#include <iostream>
using namespace std;

#include "SDR_Host.h"
#include "include/AppCommon.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>

#define MSGQ_KEY_TX 15
#define MSGQ_SNMP_KEY 40

#define SHM_GPS_KEY 1150
#define SHM_GPS_SIZE 1024


/* msgid for msgsnd() to DSP */
SI_32 g_ip_Mid_Tx;

void slotAllocationTableInfo(SI_32 );
void mbitTest(SI_32 );

SI_32 App_messagesend(Msg_st *msg_obj, UI_32 len)
{
	SI_32 loc_status;
	loc_status = msgsnd(g_ip_Mid_Tx, msg_obj, len, 0);
	if (loc_status < 0)
	{
		perror("msgsnd() in RxmHandler failed");	
		return -1;   
	}

	return 1;
}

PREPARE_LOGGING(SDR_Host_i)

SDR_Host_i::SDR_Host_i(const char *uuid, const char *label) :
    SDR_Host_base(uuid, label)
{
    // Avoid placing constructor code here. Instead, use the "constructor" function.

}

SDR_Host_i::~SDR_Host_i()
{
}

void SDR_Host_i::constructor()
{
    /***********************************************************************************
     This is the RH constructor. All properties are properly initialized before this function is called 
    ***********************************************************************************/
}

int SDR_Host_i::serviceFunction()
{
	SI_32 i = 0;
	SI_32 j = 0;
	SI_32 k = 0;
	SI_32 loc_fd = 0;
	static Shm_Param_st *g_Shm_Seg_ptr = NULL;
	SI_32 loc_ipSnmpId = 0;
	SI_32 loc_shmid = 0;
	key_t loc_msg_key = 0;
	key_t loc_shm_key = 0;
	FILE *ptr = NULL;
	SI_32 attenVal = 0;
	SI_8 temp[100];
	SI_8 temp1[5];
	SI_8 temp2[5];
	SI_8 temp3[5];
	SI_8 temp4[5];
	UI_32 RxGain = 0;
	SI_32 battery = 0;
	SI_32 nblist[64];
	SL_32 nbvalue[7];
	SI_8 loc_line[350];
	SI_32 loc_status = 0;
	SI_32 loc_count = 0;
	SI_32 RSSI[SLOTS_PER_SUPERFRAME];
	SI_8 bose_config[45][18];
	struct ifreq loc_ifr;

	/* Creating shared memroy */
	loc_shm_key = ftok("/home/root", SHM_SEG_KEY);
	if((loc_shmid = shmget(loc_shm_key, SHM_SEG_SIZE, 0666)) < 0)
	{
		perror("shmget() failed");
		LOG_INFO(SDR_Host_i,"shmget() failed");
		return -1;
	}

	if((g_Shm_Seg_ptr = (Shm_Param_st *)shmat(loc_shmid, NULL, 0)) == (Shm_Param_st *) -1)
	{
		perror("shmat() failed");
		LOG_INFO(SDR_Host_i,"shmat() failed");
		return -1;
	}

	/* Creating message queue to send data from ARM to DSP */ 
	loc_msg_key = ftok("/home/root", MSGQ_KEY_TX);
	g_ip_Mid_Tx = msgget(loc_msg_key, 0666 | IPC_CREAT);
   
	if(g_ip_Mid_Tx < 0)
	{
		LOG_INFO(SDR_Host_i,"msgget() failed\n");
	}

	/*Get messageQ Id created by server to receive data*/
	key_t loc_msg_key_Rx;
	loc_msg_key_Rx = ftok("/home/root/", MSGQ_SNMP_KEY);
	loc_ipSnmpId = msgget(loc_msg_key_Rx, IPC_CREAT | 0666);

	if(loc_ipSnmpId < 0)
	{
		LOG_INFO(SDR_Host_i,"msgget failed\n");
	}

	/* SDR device parameters
 	 * 1. GPS co-ordinates
 	 */	
	ptr = popen("/home/root/digital_cmdline 1 9 0", "r");

	if(NULL == ptr)
	{
		LOG_INFO(SDR_Host_i,"GPS command not executed successfully");
	}
        
	LOG_INFO(SDR_Host_i,"GPS_Longitude : " << g_Shm_Seg_ptr->gps_info.gps_longitude << " GPS_Latitude : " << g_Shm_Seg_ptr->gps_info.gps_latitude << "\n");
	g_Shm_Seg_ptr->gps_longitude = g_Shm_Seg_ptr->gps_info.gps_longitude;
	g_Shm_Seg_ptr->gps_latitude = g_Shm_Seg_ptr->gps_info.gps_latitude;   
	g_Shm_Seg_ptr->luid = 0;       
	pclose(ptr);

	// Tx Attenuation
	ptr = popen("/home/root/digital_cmdline 1 2 0 | grep Tx | cut -d':' -f2", "r");
	memset(temp, 0, sizeof(temp));
	fgets(temp, sizeof(temp),ptr);
	attenVal = atoi(temp);
	LOG_INFO(SDR_Host_i,"Attenuation : " << attenVal << "\n");
	pclose(ptr);


	ptr = popen("cat /sys/class/thermal/thermal_zone1/temp | sed 's/00$//' | sed 's/.$/.&/'", "r");
	memset(temp, 0, sizeof(temp));
	fgets(temp, sizeof(temp),ptr);
	memset(&temp1, 0, sizeof(temp1));
	memcpy(temp1, temp, strlen(temp)-1);
	pclose(ptr);

	ptr = popen("cat /sys/class/thermal/thermal_zone2/temp | sed 's/00$//' | sed 's/.$/.&/'", "r");
	memset(temp, 0, sizeof(temp));
	fgets(temp, sizeof(temp),ptr);
	memset(&temp2, 0, sizeof(temp2));
	memcpy(temp2, temp, strlen(temp)-1);
	pclose(ptr);

	ptr = popen("cat /sys/class/thermal/thermal_zone3/temp | sed 's/00$//' | sed 's/.$/.&/'", "r");
	memset(temp, 0, sizeof(temp));
	fgets(temp, sizeof(temp),ptr);
	memset(&temp3, 0, sizeof(temp3));
	memcpy(temp3, temp, strlen(temp)-1);
	pclose(ptr);

	ptr = popen("cat /sys/class/thermal/thermal_zone4/temp | sed 's/00$//' | sed 's/.$/.&/'", "r");
	memset(temp, 0, sizeof(temp));
	fgets(temp, sizeof(temp),ptr);
	memset(&temp4, 0, sizeof(temp4));
	memcpy(temp4, temp, strlen(temp)-1);
	pclose(ptr);

	LOG_INFO(SDR_Host_i, "Temp1 : " << temp1 << " Temp2 : " << temp2 << " Temp3 : " << temp3 << " Temp4 : " << temp4 << "\n");

	//Rx Gain
	ptr = popen("/home/root/digital_cmdline 1 3 0 | grep Rx | cut -d':' -f2", "r");
	if(NULL == ptr)
	{
		LOG_INFO(SDR_Host_i,"RxGain Command not executed\n");
	}
	else
	{
		memset(temp, 0, sizeof(temp));
		fgets(temp, sizeof(temp),ptr);
		RxGain = atoi(temp);
		LOG_INFO(SDR_Host_i, "Rx Gain : " << RxGain << "\n");
		pclose(ptr);
	}

	//Frequency
	LOG_INFO(SDR_Host_i, "Frequency in MHz : " << g_Shm_Seg_ptr->tx_freq/1000000 << "\n");

	//Battery Capacity
	ptr = popen("cat /sys/class/power_supply/sbs-0-000b/capacity", "r");
	if(NULL == ptr)
	{
		LOG_INFO(SDR_Host_i,"/sys/class/power_supply/sbs-0-000b/capacity file is not created which means Unit is not using Battery!\n");
		shmdt(g_Shm_Seg_ptr);
		return 0;
	}
	memset(temp, 0, sizeof(temp));
	fgets(temp, sizeof(temp),ptr);
	battery = atoi(temp);
	LOG_INFO(SDR_Host_i, "Battery Capacity of Gateway Node" << battery << "\n");
	pclose(ptr);

	//Available Neighour list LUID
	ptr = popen("/home/root/shm_rd_wr 1 19 | grep nblist | cut -d':' -f2", "r");

	if(NULL == ptr)
	{
		LOG_INFO(SDR_Host_i,"nblist command is not executed\n");
	}
	else
	{
		memset(loc_line, 0, sizeof(loc_line));
		memset(temp, 0, sizeof(temp));
		memset(nbvalue, 0, sizeof(nbvalue));
		fgets(loc_line, 350, ptr);

		strcpy(temp,strtok(loc_line, "-"));
		nbvalue[0] = atoi(temp);

		strcpy(temp,strtok(NULL, "-"));
		nbvalue[1] = atoi(temp);

		strcpy(temp,strtok(NULL, "-"));
		nbvalue[2] = atoi(temp);

		strcpy(temp,strtok(NULL, "-"));
		nbvalue[3] = atoi(temp);

		strcpy(temp,strtok(NULL, "-"));
		nbvalue[4] = atoi(temp);

		loc_count = 0;
		memset(&nblist, 0, sizeof(nblist));
		for(i = 0; i < 5; i++)
		{
			for(j = 0; j<64; j++)
			{
				loc_status = nbvalue[i]>>j&1;
				if(1 == loc_status)
				{
					nblist[loc_count] = j+1;
					loc_count++;
				}
			}
		}

		if(0 == loc_count)
		{
			LOG_INFO(SDR_Host_i," Self LUID : 0");
		}
		else
		{
			for(i=loc_count-1; i>=0; i--)
			{
				LOG_INFO(SDR_Host_i," Neighours : " << nblist[i]);
			}
		}
	}
	pclose(ptr);

	// RSSI
	ptr = popen("/home/root/digital_cmdline 1 4 0", "r");

	if(NULL == ptr)
	{
		LOG_INFO(SDR_Host_i, "RSSI Command not executed\n");
	}
	else
	{
		fgets(loc_line, sizeof(loc_line), ptr);
		loc_count = 1;
		i = 0;
		while(fgets(loc_line, sizeof(loc_line), ptr) != NULL)
		{
			if(loc_count > 8)
			{
				RSSI[i] = atoi(strtok(loc_line, "\t"));
				i++;
				k = 1;
				while(k<10)
				{
					RSSI[i] = atoi(strtok(NULL, "\t"));
					i++;
					k++;
				}
			}
			loc_count++;
		}

	}
	j = 1;
	for(i = 0; i < SLOTS_PER_SUPERFRAME; i++)
	{
		LOG_INFO(SDR_Host_i, "RSSI : " << RSSI[i]);
		if((i+1)%10==0)
		LOG_INFO(SDR_Host_i,"\n");
	}
	pclose(ptr);

	//PER information
	ptr = popen("/home/root/digital_cmdline 1 a 0", "r");

	if(NULL == ptr)
	{
		LOG_INFO(SDR_Host_i, "PERINFO Command not executed\n");
	}

	LOG_INFO(SDR_Host_i, " PER Window Info :\n");
	LOG_INFO(SDR_Host_i, " Per window size: " << g_Shm_Seg_ptr->gstatus_info.per_window_size <<" Rx pkts for per: " << g_Shm_Seg_ptr->gstatus_info.rx_pkts_for_per <<" total rx chckm fail: " << g_Shm_Seg_ptr->gstatus_info.total_rx_chksum_fail <<" PER: " << g_Shm_Seg_ptr->gstatus_info.PER <<" overall chksum fail: " << g_Shm_Seg_ptr->gstatus_info.overall_chksum_fail);
	pclose(ptr);


	//IP Address of device
	loc_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(loc_fd < 0)
	{
		LOG_INFO(SDR_Host_i, "Failed to created socket at IP Address\n");
		close(loc_fd);
		shmdt(g_Shm_Seg_ptr);
		return 0;
	}

	loc_ifr.ifr_addr.sa_family = AF_INET;
	strncpy(loc_ifr.ifr_name, "eth0", IFNAMSIZ-1);
	ioctl(loc_fd, SIOCGIFADDR, &loc_ifr);
	close(loc_fd);

	LOG_INFO(SDR_Host_i, "Ip Address : " << (inet_ntoa(((struct sockaddr_in *)&loc_ifr.ifr_addr)->sin_addr)));


	//MAC address
	loc_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(loc_fd < 0)
	{
		LOG_INFO(SDR_Host_i,"Failed to created socket at Mac Address\n");
		close(loc_fd);
		shmdt(g_Shm_Seg_ptr);
		return 0;
	}
	loc_ifr.ifr_addr.sa_family = AF_INET;
	strncpy(loc_ifr.ifr_name,"eth0", IFNAMSIZ-1);
	ioctl(loc_fd, SIOCGIFHWADDR, &loc_ifr);

	printf("\nMac Address : %02x:%02x:%02x:%02x:%02x:%02x \n", loc_ifr.ifr_hwaddr.sa_data[0],
                        loc_ifr.ifr_hwaddr.sa_data[1], loc_ifr.ifr_hwaddr.sa_data[2], loc_ifr.ifr_hwaddr.sa_data[3],
                        loc_ifr.ifr_hwaddr.sa_data[4], loc_ifr.ifr_hwaddr.sa_data[5]);
	LOG_INFO(SDR_Host_i," Mac Address : "<< loc_ifr.ifr_hwaddr.sa_data[0] << loc_ifr.ifr_hwaddr.sa_data[1] << loc_ifr.ifr_hwaddr.sa_data[2]
                                             << loc_ifr.ifr_hwaddr.sa_data[3] << loc_ifr.ifr_hwaddr.sa_data[4] << loc_ifr.ifr_hwaddr.sa_data[5]);
	close(loc_fd);

	//BOSE Config details
	ptr = popen("/home/root/bose_config d", "r");
	if(ptr == NULL)
	{
		LOG_INFO(SDR_Host_i,"Bose config command is not executed successfully");
	}
	else
	{
		memset(&bose_config, 0, sizeof(bose_config));
		memset(&loc_line, 0, sizeof(loc_line));
		fgets(loc_line, sizeof(loc_line), ptr);
		fgets(loc_line, sizeof(loc_line), ptr);
		i = 0;
		loc_count = 1;
		printf("\n");
		cout << "Bose Config details : " << endl;
		while(fgets(loc_line, sizeof(loc_line), ptr) != NULL)
		{
			LOG_INFO(SDR_Host_i, "\n" << loc_line);
		}
		pclose(ptr);
	}

	return 0;
}
