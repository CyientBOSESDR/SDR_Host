/******************************************************************************
 * FILE NAME: IP_Routing.h                                                    *
 *                                                                            *
 * PURPOSE: This header file consists definition of ping & SNMP structures,   *       
 *          ping & SNMP functions and Macros                                  *
 *                                                                            *
 * GLOBAL VARIABLES:                                                          *
 *                                                                            *
 * Variable                 Type                Description                   *
 *                                              link list.                    *
 * DEVELOPMENT/ CHANGE HISTORY:                                               *
 *                                                                            *
 * Date       Author            Release         Description Of Change         *
 * 18/08/20   Lakshminaidu      3.1.0           None                          *
 *                                                                            *
 *                                                                            *
 *****************************************************************************/
#ifndef __IP_ROUTING_H__
#define __IP_ROUTING_H__

/*IP_Routing Header files*/ 

#include <SDR_Std.h>
#include <errno.h>
#include <sys/ioctl.h>         //ioctl();
#include <sys/socket.h>        //socket() to create
#include <netinet/in.h>        //sockaddr_in, in_addr, protocol like IPPROTO_ICMP, IPPROTO_UDP etc 
#include <arpa/inet.h>         //inet_addr
#include <linux/if_arp.h>      //ARPOP_REQUEST
#include <netinet/ip_icmp.h>   //icmphdr
#include <netinet/udp.h>       //udphdr
#include <linux/if_ether.h>    //ETH_P_ALL

#include <AppCommon.h>
#include <pthread.h>
#include <BoseCfg.h>


#define PACKETSIZE 128
#define MAX_PACKET_SIZE 1560

#define ETH_HWLEN  6
#define IP_ADDRLEN 4

#define DSPTOARMTYPE 0
#define ARMTOHOSTTYPE 1

#define ICMP_PROTO 1
#define UDP_PROTO 17

#define SNMPGETSETREQUEST 1
#define SNMPGETRESPONSE 2

#define PING 1
#define SNMPPROCESS 2

#pragma pack(1)

enum Snmp_Request_Type
{
   SNMPGPS = 2,
   SNMPSETFREQ,
   SNMPTEMP,
   SNMPGETATTEN,
   SNMPBATTERY,
   SNMPSETATTEN,
   SNMPGETNBLIST,
   SNMPGETRxGAIN,
   SNMPGETL1STATUS,
   SNMPGETRSSI,
   SNMPGETPCL,
   SNMPGETL3STATUS,
   SNMPGETL2STATUS,
   SNMPGETPERINFO,
   SNMPSETWAVEFORM,
   SNMPGETFREQ,
   SNMPGETSLOTINFO,
   SNMPDELETEDATA,
   SNMPDELETEALLFILES,
   SNMPLOADKERNELMODULES,
   SNMPREMOVEKERNELMODULES,
   SNMPLISTOFKERNELMODULES,
   SNMPPOWEROFFDEVICE,
   SNMPGETIPADDRESS,
   SNMPGETSWVERSION,
   SNMPGETMACADDRESS,
   SNMPGETMBITSTATUS,
   SNMPGETBERINFO,
   SNMPGETBOSECONFIG,
   SNMPGETWAVEFORM, 
   SNMPDELENCRYPTION,
};

/*****structure definitions*****/

struct ethheader  //Ethernet header
{
  UI_8 srca[6];
  UI_8 dsta[6];
  SI_16 type;
};

typedef struct lookup  //Lookup Table
{
  SI_32 luid;
  SI_8 *ip_addr;
}lookup_st;

typedef struct data_header //local header data
{
	SI_8 id;
	SI_8 type;
	SI_8 subtype;
	SI_16 len;
	SI_8 snmpRequest;
}dataheader_st;  //5 bytes

typedef struct ping_pkt //icmp packet
{
   struct iphdr iph;
   struct icmphdr icmp;  
   SI_8 msg[PACKETSIZE-sizeof(struct icmphdr)];
}pingpkt_st;  

typedef struct packet_data //icmp packet + local header 
{
	dataheader_st header;
	pingpkt_st data;
}packetdata_st;

typedef struct {
    SL_32 msgtype;
    UI_8 producer_id;
    UI_8 payload[MAX_PACKET_SIZE];
}IpMsgRx_st;

typedef struct freqbuff
{
   SI_8 freqval[10];
}freqbuff_t;

typedef struct tempbuff
{
   SI_8 temp1[5];
   SI_8 temp2[5];
   SI_8 temp3[5];
   SI_8 temp4[5];
}tempbuff_t;

typedef struct attenbuff
{
   SL_32 power_atten;
}attenbuff_t;

typedef struct batterybuff
{
   SI_16 capacity;
}batterybuff_t;

typedef struct rxgainbuff
{
   UI_32 rxgaindata;
}rxgainbuff_t;

typedef struct l1statusbuff
{
   FL_32 c1FreqOff;
   FL_32 c2FreqOff;
   SI_32 slotStartPos;
   FL_32 totalFreqOff;
   SI_32 maxCorrVal;
   FL_32 snr;  
   SI_32 rxValidCount;
}l1statusbuff_t;

typedef struct rssibuff
{
   UI_32 RSSI[SLOTS_PER_SUPERFRAME];
}rssibuff_t;

typedef struct pclbuff
{
   UI_32 broadcast_tx_count;
   UI_32 broadcast_rx_count;
   UI_32 data_tx[MAX_QOS];
   UI_32 data_rx[MAX_QOS];
   UI_32 data_relay[MAX_QOS];
}pclbuff_t;

typedef struct routingbuff
{
   SI_32 routing_info[OID_ROUTING_MIB_SIZE];
}routingbuff_t;

typedef struct mac_upstbuff
{
   SI_32 generic_upstream_mib[MAC_GENERIC_MIB_SIZE];
   SI_32 rach_upstream_mib[MAC_RACH_MIB_SIZE];
   SI_32 system_map_upstream_mib[MAC_SYSTEM_MAP_MIB_SIZE];
   SI_32 broadcast_upstream_mib[MAC_BROADCAST_MIB_SIZE];
   SI_32 data_phase_upstream_mib[MAC_DATA_PHASE_MIB_SIZE];
}mac_upstbuff_t;

typedef struct perinfo
{
   UI_32 per_window_size;
   SI_32 rx_pkts_for_per;
   SI_32 total_rx_chksum_fail;
   FL_32 PER;
   SI_32 overall_chksum_fail; 
}perinfo_t;

typedef struct waveformbuff
{
   SI_32 waveformValue;
}waveformbuff_t;

typedef struct slotbuff
{

}slotbuff_t;

typedef struct getfreqbuff
{
   UI_32 getFreqVal;
}getfreqbuff_t;

typedef struct deldata_buff
{
   SI_8 filePath[50];
}deldatabuff_t;

typedef struct kernelModule_buff
{
   SI_8 modulepath[50];
   SI_32 moduleRequest;
}kernelModulebuff_t;

typedef struct ipAddress_buff
{
   SI_8 ipAddress[18];
}ipAddressbuff_t;

typedef struct swVersion_buff
{
   UI_8	fpga_bit_major_ver;
   UI_8	fpga_bit_minor_ver;
   UI_8	sl_mod_sw_major_ver;
   UI_8	sl_mod_sw_minor_ver;
   UI_8	sl_demod_sw_major_ver;
   UI_8	sl_demod_sw_minor_ver;
   UI_8	l2_sw_major_ver;
   UI_8	l2_sw_minor_ver;
   UI_8	arm_sw_major_ver;
   UI_8 arm_sw_minor_ver;
}swVersionbuff_t;

typedef struct macAddress_buff
{
   UI_8 macAddress[6];
}macAddressbuff_t;

typedef struct mbitTestInfo_buff
{
   SI_32 mbitTestId;
   SI_8 mbitTestInfo[20][40];
}mbitTestInfobuff_t;

typedef struct berInfo_buff
{
   SI_32 berRxErrorBits;
   FL_32 berAvg;
}berInfobuff_t;

typedef struct MAC_ID_BUFF_t
{
   UI_8 macaddr[12];
}MAC_ID_BUFF_t;

typedef struct VERSION_BUFF
{
   UI_8 version[9];
}VERSION_BUFF_t;

typedef struct
{
   UI_32 magicnum;
   UI_8 serial_number;
   UI_32 mission_id;
   UI_8 wavefrom_id;
   UI_8 priority;
   UI_32 model_id;
   ipAddressbuff_t ip_addr;
   UI_8 luid;
   UI_8 bbctl_serial_no;
   UI_8 bbctl_model_no;
   VERSION_BUFF_t dsp_version;
   VERSION_BUFF_t fpga_version;
   VERSION_BUFF_t slmod_ver_wave0;
   VERSION_BUFF_t sldemod_ver_wave0;
   VERSION_BUFF_t slmod_ver_wave1;
   VERSION_BUFF_t sldemod_ver_wave1;
   VERSION_BUFF_t slmod_ver_wave2;
   VERSION_BUFF_t sldemod_ver_wave2;
   VERSION_BUFF_t slmod_ver_wave3;
   VERSION_BUFF_t sldemod_ver_wave3;
   UI_8     trx_card_slno;
   UI_8     trx_card_modelno;
   UI_8     fem_rx_slno;
   UI_8     fem_rx_modelno;
   UI_8     fem_tx_slno;
   UI_8     fem_tx_modelno;
   UI_8     pa_slno;
   UI_8     pa_modelno;
   UI_8     battery_slno;
   UI_8     battery_modelno;
   UI_8     hrf_slno;
   UI_8     hrf_modelno;
   UI_8     keypad_slno;
   UI_8     keypad_modelno;
   UI_8 strid;
   MAC_ID_BUFF_t  mac_addr;
   UI_16 dummy;
   UI_8 pttontme;
   UI_8 pttoffmfact;
   UI_8 lcd_brightness;
   UI_8 lcd_timeout;
   UI_32 chk_sum;
}bose_configparams_buff_t;

typedef union 
{
   //bose_configparams_buff_t SnmpCfgParams;   
   berInfobuff_t berInfo;
   //mbitTestInfobuff_t mbitTestInfo;  
   macAddressbuff_t macAddr;
   swVersionbuff_t swVersion;            
   ipAddressbuff_t ipAddr;
   //kernelModulebuff_t kernelModule;  
   deldatabuff_t deldata;         
   getfreqbuff_t getfreq;
   //slotbuff_t slotinfo;           
   waveformbuff_t waveform;             
   perinfo_t per_window;         
   //mac_upstbuff_t mac_info;       
   //routingbuff_t routing;         
   //pclbuff_t pcl;                 
   //rssibuff_t rssi;               
   //l1statusbuff_t l1status;       
   rxgainbuff_t rxgain;
   batterybuff_t battery;
   attenbuff_t  atten;
   tempbuff_t temp;
   freqbuff_t freqbuff;
   gpsinfo_t gps_info;
}payload_ut;

typedef struct snmppacketdata
{   
   dataheader_st header;
   payload_ut payload;
}snmppacketdata_st; 

typedef struct 
{
   SL_32 mtype;
   snmppacketdata_st snmppkt;
}ipmsg_st;

struct arp_header  //ARP packet 28 bytes
{
   UI_16 hardware_type;
   UI_16 proto_type;
   UI_8 hardware_len;
   UI_8 proto_len;
   UI_16 opcode;
   UI_8 sender_mac[6];
   UI_8 sender_ip[4];
   UI_8 recv_mac[6];
   UI_8 recv_ip[4];
};

/* Frequency */
typedef struct armMsgBuf
{
   SL_32 msgtype;
   SI_8 sourceId;
   SI_8 msgBuff[768];
}armMsgBuf_t;

#pragma pack()

/*****Function declaration*****/

/* Ping Functions */
SI_32 NetToAscii(UL_32 );
SI_32 compare_subnet(SI_8 *, SI_8 *);
void *Listener();
SI_32 PingArmToDsp(struct iphdr*, SI_32);
void PingArmToHost(struct iphdr *pckt_buf);
SI_32 LookupIp(SI_32);
SI_32 LookupLuid(SI_8 *);
SI_8 *GetSystemIp();
SI_32 PingDspToArm(pingpkt_st *, SI_32);
UI_16 Checksum(void *ptr, SI_32 len);
void HandleARP();
void IpRouteinit();
void DigDataProcess(packetdata_st *,SI_32 luid);

void *IPmsgRxThread();

/* Snmp Functions */
void SnmpProcess(SI_32 , UI_8 *);

void ipMsgRxSend(SI_32, UI_8 *);

void SnmpGps(SI_32);                      
void SnmpTemp(SI_32);                     
void SnmpGetAtten(SI_32);                 
void SnmpBattery(SI_32);  		  
void SnmpSetAtten(SI_32, UI_8 *);	  
void SnmpGetRxGain(SI_32);                
void SnmpGetL1Status(SI_32);  		  
void SnmpGetRssi(SI_32);  		  
void SnmpGetPcl(SI_32);  		  
void SnmpGetL3Status(SI_32);  		  
void SnmpGetL2Status(SI_32);  		  
void SnmpGetPer(SI_32);  
void SnmpSetWaveform(SI_32, UI_8 *);
void SnmpGetFreq(SI_32); 
void SnmpGetSlot(SI_32); 
void SnmpDelData(SI_32, UI_8 *);
void SnmpDelDataAll(SI_32, UI_8 *);
void SnmpManageKernelModule(SI_32, UI_8 *);
void SnmpPowerOffDevice(SI_32, UI_8 *);
void SnmpGetIpAddress(SI_32); 
void SnmpGetSwVersion(SI_32); 
void SnmpGetMacAddress(SI_32); 
void SnmpGetMbitTest(SI_32, UI_8 *);
void SnmpGetBerInfo(SI_32 luid);
void SnmpGetBoseConfig(SI_32);
void SnmpGetWaveform(SI_32);
void SnmpDelEncryption(SI_32, UI_8 *);

#endif
