/*
 * Copyright (c) 2013-2014, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== AppCommon.h ========
 *
 */

#ifndef AppCommon__include
#define AppCommon__include
#if defined (__cplusplus)
extern "C" {
#endif

#include <time.h>
#include <stdint.h>
#include "SDR_Std.h"
#include <stdbool.h>

#include "sec_arm_dsp_intf.h"
#define META_DATA_HEADER  0x55
#define FDU1	          0x2
#define DATA_PATH_ID	  0x1
#define CONTROL_PATH_ID   0X1
#define LOOP_BACK_ID      0x2
#define TOTAL_SZ	  576
#define TX_START          0xA
#define TX_ID             0x01
#define RX_ID             0x00 

#define ARM_SW_MAJOR_NUM   0x03 //first nible specify the test/release version
                                //0-->release, 1,2,...-->test version
#define ARM_SW_MINOR_NUM   1

#define DEBUG_FILE_PRINT   1 
#define DEBUG_FILE_PRINT_DISABLE  0
#define SHM_SEG_KEY		1250
#define SHM_SEG_SIZE            2048
#define SHM_CTRL_FLAG_KEY       45
#define ANALOG_MODE		0
#define DIGITAL_MODE		1
#define CONTROL_PLANE		0
#define DATA_PLANE		1
#define START			0x1
#define STOP			0x2
#define ARM			0
#define DSP			1
#define TRUE			1
#define FALSE			0
#define L2_LAYER		2
#define DEFAULT			0
#define LOOPBACK		1
#define MSG_TYPE_DSP		11
#define MSG_TYPE_ARM		12
#define MSG_TYPE_BITE   13
#define BUFSIZE_MAX		256
#define BUFSIZE_MIN		160
#define ON               1
#define OFF              0
#define ONE_BLOCK	 1
#define WAIT_INDEFINITE                (~(0))
#define POLL_TIMEOUT 1
#define IPC_WAIT_SUCCESS 1
//#define TX_LOG_REPORT
//#define RX_LOG_REPORT

/*
 *  ======== Application Configuration ========
 */


#define MSG_PACKET_DATA_SZ	2048
#define META_DATA_SZ	        64
#define RES_META_SZ_TX	        50
#define RES_META_SZ	        2
#define RES_META_SZ_1	        32
#define PAYLOAD_SZ	        768 //256  //max packet size is 512 for analog, will add some buffer

#define NUM_PC_SLOTS          16
#define NUM_DATA_SLOTS        7
#define SLOTS_PER_SUPERFRAME        100
#define MAC_GENERIC_MIB_SIZE        0x0008
#define MAC_RACH_MIB_SIZE           0x0009
#define MAC_SYSTEM_MAP_MIB_SIZE     0x001A
#define MAC_BROADCAST_MIB_SIZE      0x0010
#define MAC_DATA_PHASE_MIB_SIZE     0x0018
#define OID_ROUTING_MIB_SIZE        0x0013
#define MAX_QOS 4

#define DIGI_NO_HOPS  100
#define DIGI_NO_NODS  16
#define NODE_STATE_UNDEFINED 0
#define NODE_STATE_TRANS 1
#define NODE_STATE_RECV  2
#define NODE_STATE_TRANS_MULTI  3
#define NODE_STATE_BLOCK_T  4
#define NODE_STATE_COLLISION  5
#define NODE_STATE_IDLE  6

#define LCD_BRIGHTNESS_MAX    0x7
#define LCD_BRIGHTNESS_MID    0x5
#define LCD_BRIGHTNESS_MIN    0x3
#define LCD_BRIGHTNESS_OFF    0x1

#define LCD_BKLIGHT_DIM       0x10
#define LCD_BKLIGHT_BRIGHT    0x20


typedef int (*fhprasndcb)(UI_32 *,UI_32 ,UI_8 );

enum wf_id
{
   FM_MOD   =  0,
   SSB_AM_MOD,
   DSB_AM_MOD,
   NB_CPFSK,
   NB_CPFSK_FH100,
   WB_CPFSK,
   /*Add new wave form id here*/
   WF_ID_MAX
};

enum Test_Id{
	ARM_CP_LOOPBACK   = 0x1,
	ARM_FPGA_LOOPBACK,
	ARM_SL_LOOPBACK,
	ARM_PCIE_LOOPBACK
};

enum Packet_Type{
	VOICE    = 0x1,
	GPS,
        SMS,
        MBIT,
	DSP_CTRL,
	ADC_CAPTURE_PKT,
	DIG_VOICE,
	DIG_DATA,
	BITE_TEST
};

enum BITE_TEST_Field_val{
	DSP_TEST=1
}; 



enum squelch_cfg
{
   SQUELCH_DISABLE,
   NATO,
   SINGLE_TONE_ENABLE,
   DUAL_TONE_ENABLE
};

enum Dsp_Ctrl_Field_Val{
	GET_FPGA_BIT_VER    = 0x1,
	GET_SL_MOD_SW_VER,
	GET_SL_DEMOD_SW_VER,
	GET_L2_SW_VER,
	SET_S1_FREQ,
	SET_S2_FREQ,
	SET_S1_DEV_FREQ,
	SET_S2_DEV_FREQ,
	SET_S1_TONE_AMP,
	SET_S2_TONE_AMP,
	//SQUELCH_TONE_ENABLE,
   //DUAL_TONE_ENABLE,
   SQUELCH_CONFIG,
	DSP_WRITE,
	DSP_READ,
     ARM_SLCODE_DOWNLOAD,
     DSP_DRIVER_INIT,
     WF_CHANGE,

     DSP_RF_READY,
     SET_FREQ_ATTN = 0x13,
     DSP_HEARTBEAT = 0x14,
     SET_FREQ_CUSTOM =0x40,
     SET_TX_ATTN_CUSTOM,
     //added for digital
     SET_NODE_CONFIG  =0x50,
     SET_TX_ATTN,
     GET_TX_ATTN,
     SET_RX_GAIN,
     GET_RX_GAIN,
     AUTO_AGC_ENABLE,
     SET_PER_WINDOW_SZ,
     SET_L1_WINDOW_SZ,
     GET_RSSI,
     GET_L1_STATS,
     GET_L2_STATS,
     GET_L3_STATS,
     GET_PCL_STATS,
     GET_GPS_INFO,
     DSP_DIG_WF_INIT_IND,
     GET_PER,
     GET_SLOT_INFO = 0x60,
     GET_TOPOLOGY,
     SEC_PARAMS = 0x62,
     COMSEC_CTRL,
     SEND_FH_PARAMS,
     BER_MODE_CONFIG,
     DSP_EVENT, 
     DSP_MODE_GET,
	  DBG_AUDIO
	         
};

#pragma pack(1)
typedef struct {
      UI_8	meta_data_header;
      UI_8	path_id : 4;
      UI_8	meta_data_type : 4;
      UI_16	total_len;
      UI_16	meta_data_len;
      UI_16	tx_rx_switch_id;
      UI_16	payload_len;
      UI_32     tx_seq_num;
      UI_8	res_field_str[RES_META_SZ_TX];    
      UI_8	audio_payload_str[PAYLOAD_SZ];	
}Voice_Data_Arm2Dsp_st;

typedef struct {
      UI_8	meta_data_header;
      UI_8	meta_data_type : 4;
      UI_8	path_id : 4;
      UI_16	total_len;
      UI_16	meta_data_len;
      UI_8	tx_rx_switch_id;
      UI_16	payload_len;
      UI_8	res_field_str[3];
      UI_32	s1_detect_freq;
      UI_32	s2_detect_freq;
      UI_32	sig_power;
      UI_32	noise_power; 
      SI_32	rssi;    
      UI_32  fem_gain; // New  Field added to report the FEM gain
}metadata_analog;

typedef struct {
      UI_8 metadata_headr[META_DATA_SZ];
      UI_8 audio_payload_str[PAYLOAD_SZ];	
}Voice_Data_Dsp2Arm_st;

typedef struct {
    UI_8 qos;
    UI_8 producer_id;
    UI_8 consumer_id;
    UI_8 metadata_headr[META_DATA_SZ];
    UI_8 payload[PAYLOAD_SZ];
}DigitalVoiceDataPacket_st;

typedef struct {
    long msgtype;
    UI_8 producer_id;
    UI_8 payload[PAYLOAD_SZ];
}DigitalGuiDataPacket_st;

typedef struct {
      UI_16	test_id; 
      UI_8	cmd;
      UI_16	msg_num;    
}Cmd_Data_st;

typedef struct {
      UI_16	test_id; 
      UI_8	cmd;
      UI_16	msg_num;  
      UI_8	result;
      UI_16	error_code;
}Rsp_Data_st;

typedef struct {
      UI_8	cmd;
      UI_16	msg_num;
      UI_8	val;
      UI_8	flags;           
}waveform_change_st;


typedef struct {
      UI_8	cmd;
      UI_16	msg_num;
      UI_32	val;      
}Sqlch_Freq_Dev_Set_st;

typedef struct {
      UI_8	cmd;
      UI_16	msg_num;
      UI_8	result;      
}Resp_Sqlch_Freq_Dev_Set_st;

typedef struct {
      UI_8	cmd;
      UI_16	msg_num;
      UI_8	val;           
}Sqlch_Dual_En_st;

typedef struct {
      UI_8	cmd;
      UI_16	msg_num;
      UI_8	result;      
}Resp_Sqlch_Dual_En_st;

typedef struct {
      UI_8	cmd;
      UI_16	msg_num;      
}Dsp_Sw_Ver_st;

typedef struct {
      UI_8	cmd;
      UI_16	msg_num;
      UI_8	mazor_ver;
      UI_8	minor_ver;      
}Resp_Dsp_Sw_Ver_st;


typedef struct {
      UI_8	cmd;
      UI_16	msg_num;
      UI_32	address;      
}Dsp_Rd_st;

typedef struct {
      UI_8	cmd;
      UI_16	msg_num;
      UI_32	address;
      UI_32	data;
      UI_8	ack;      
}Resp_Dsp_Rd_st;

typedef struct {
      UI_8	cmd;
      UI_16	msg_num;
      UI_32	address;
      UI_32	data;      
}Dsp_Wr_st;

typedef struct {
      UI_8	cmd;
      UI_16	msg_num;
      UI_32	address;
      UI_8	ack;      
}Resp_Dsp_Wr_st;

//digital part
typedef struct
{
      UI_8	cmd;
      UI_16	msg_num;
      SI_32 val;
}ctrl_power_st;

typedef struct
{
      UI_8	cmd;
      UI_16	msg_num;
      SI_32 val;      
}tx_attn_t;
typedef struct {
      UI_8	cmd;
      UI_16	msg_num;
      SI_32 val;      
}rx_gain_t;

typedef struct{
	UI_8 cmd;
	SI_32 value;
}dbg_st;	
typedef struct{
	UI_8 cmd;
	UI_16 msg_num;
	UI_32 testid;
	UI_32 testid_ext;
	UI_32 test_status;
}bitconf_st;
typedef struct {
      UI_8	cmd;
      UI_16	msg_num;
      UI_8 val;      
}autoagc_enable_t;

typedef struct {
      UI_8	cmd;
      UI_16	msg_num;
      UI_32 val;      
}per_window_size_t;      

typedef struct {
      UI_8	cmd;
      UI_16	msg_num;
      UI_32 val;      
}l1stats_window_size_t;   

typedef struct
 {
      UI_8	cmd;
      UI_16	msg_num;
      UI_8 val;      
}gen_dsp8_cmd_t;   

typedef struct phy_stats 
{
    UI_8	cmd;
    UI_16	msg_num;
    FL_32 c1_freq_off;
    FL_32 c2_freq_off;
    SI_32 slot_start_pos;
    FL_32 total_freq_off;
    SI_32 max_corr_value;
    FL_32 snr;
    UI_32 rx_valid_cnt;
} l1statistics_t;


typedef struct mac_upst_stats
 {
    UI_8	cmd;
    UI_16	msg_num;
    SI_32 generic_upstream_mib[MAC_GENERIC_MIB_SIZE];
    SI_32 rach_upstream_mib[MAC_RACH_MIB_SIZE];
    SI_32 system_map_upstream_mib[MAC_SYSTEM_MAP_MIB_SIZE];
    SI_32 broadcast_upstream_mib[MAC_BROADCAST_MIB_SIZE];
    SI_32 data_phase_upstream_mib[MAC_DATA_PHASE_MIB_SIZE];
} mac_statistics_t;

typedef struct routing_stats
{
    UI_8	cmd;
    UI_16	msg_num;
    int routing_info[OID_ROUTING_MIB_SIZE];
} routing_statistics_t;

typedef struct PCL_PKT_STAT
{
      UI_8	cmd;
      UI_16	msg_num;
		UI_32 broadcast_tx_count;
		UI_32 broadcast_rx_count;
		UI_32 data_tx[MAX_QOS];
		UI_32 data_rx[MAX_QOS];
      UI_32 data_relay[MAX_QOS];
} t_pcl_pkt_stat;


/* New structure for waveform parameters */
typedef struct waveformcfgparams
{
    UI_8 waveform_type;
    UI_8 is_wide_band_sysmap_ack;
    UI_16 max_broadcast_payload_size;
    UI_8 max_neighbours;
    UI_8 permanent_color_count;
    UI_8 temporary_color_count;
    UI_8 luid_len;
    UI_8 fld_smframe_format_pkt_type_len;
    UI_8 fld_smframe_format_protocol_type_len;
    UI_8 fld_smframe_format_tx_slot_number_len;
    UI_8 fld_fragpayload_subheader_format_payload_length_len;
    UI_8 fld_packedpayload_subheader_format_payload_length_len;
    UI_8 max_manet_size;
    UI_16 max_pc_slot_bw_bytes;
    UI_16 max_meta_l1_pc_slot_bw_bytes;
    UI_16 max_l1_ds_slot_bw_bytes;
    UI_16 max_meta_l1_ds_slot_bw_bytes;
    UI_16 max_ds_slot_bw_bytes;
    UI_16 max_datafrag_payload_space;
    UI_8 max_pack_payload_count;
    UI_16 mac_dataphase_mtu;
    UI_8 max_frag_count;
    UI_8 data_slots_count;
    UI_16 max_slots_in_frame;
    UI_16 max_l1_bc_slot_bw_bytes;
    UI_16 max_bc_slot_bw_bytes;
    UI_16 mac_broadcast_mtu;
    UI_16 max_meta_l1_bc_slot_bw_bytes;
} waveform_cfgparams_st;


typedef struct node_config
 {
    UI_8 node_luid;
    UI_8 string_id;
    UI_8 pc_slot_owners[NUM_PC_SLOTS];
    UI_8 data_slot_owners[NUM_DATA_SLOTS];
    UI_32 freq_hop_config;
    FL_32 ad_rf_oper_freq;
    UI_8 node_string[NUM_PC_SLOTS];
    waveform_cfgparams_st wfcfgparams;
}nodeconfig_t;

typedef struct gps_info
 {
    UI_8	cmd;
    UI_16	msg_num;
    UI_16 year;
    UI_8 month;
    UI_8 day;
    UI_8 hour;
    UI_8 min;
    UI_8 sec;
    SI_32 gps_longitude;
    SI_32 gps_latitude;
    bool gps_lock_status;
}gpsinfo_t;





typedef struct 
{
      UI_8	cmd;
      UI_16	msg_num;
      nodeconfig_t nodeconfig_val;      
}nodeconfig_msg_t;



typedef struct 
{
      UI_8	cmd;
      UI_16	msg_num;
      SI_32 RSSI[SLOTS_PER_SUPERFRAME];      
}rssi_info_t;


typedef enum GPS_State
{
    GPS_INIT_STATE,
    GPS_LOCK_WAIT_STATE,
    GPS_LOCK_FAILED_STATE,
    GPS_LOCKED_STATE,
}GPS_State_enum;

typedef struct 
{
      UI_8	cmd;
      UI_16	msg_num;
      UI_32 per_window_size;
      SI_32 rx_pkts_for_per;
      SI_32 total_rx_chksum_fail;
      FL_32 PER;
      SI_32 overall_chksum_fail;      
}per_info_t;

typedef struct
{
      UI_8      cmd;
      UI_16     msg_num;
      security_params_t sec_params;
} sec_params_st;

/* structure defining freq-attn
 */
typedef struct {
      UI_8      cmd;
      UI_16     msg_num;
      UI_32		tx_freq;
      UI_32		rx_freq;
      UI_32    attn;
}attn_frequency_t;


/* structure defining freq-attn
 */
typedef struct {
      UI_8      cmd;
      UI_16 msg_num;
      UI_32 heart_beat;
}heart_beat;


/* structure defining system map
 */
typedef struct {
      SI_32		longitude;
      SI_32		latitude;
}loc_info_t;

typedef struct {
      UI_8      cmd;
      UI_16     msg_num;
      /* current superframe number 
       */
      UI_32		sf_number;
      
      /* 0-> no activity
         1-> Tx done
         2-> Rx done
         3-> checksum failure on RX
         4-> collision seen
       */ 
      UI_8		slot_activity[DIGI_NO_HOPS];
      SI_16    slot_rssi[100];
      SI_16    fem_gain[100];
      
      /* state of slot in transmitting system map schedule
         NODE_STATE_UNDEFINED=0,
         NODE_STATE_TRANS=1,
         NODE_STATE_RECV=2,
         NODE_STATE_TRANS_MULTI=3,
         NODE_STATE_BLOCK_T=4,
         NODE_STATE_COLLISION=5,
         NODE_STATE_IDLE=6,
       */
       
      UI_8     slot_schedule_state[DIGI_NO_HOPS];

		//node luid of node from which you received.
		short int rx_node_luid[100];

		//number of Received bit of every slot when node is in ber rx mode
		 short int ber_rxbits_slots[100];
		//number of error bit of every slot when node is in ber rx mode
		 short int ber_rxstatus_slots[100];
      
		FL_32    slot_snr[DIGI_NO_HOPS];
      UI_32    epoc_time;
      UI_32    frequency[DIGI_NO_HOPS];
}dnb_superframe_activity_t;


typedef struct {
   UI_32 ber_tot_rxbitcount;
   UI_32 ber_tot_rxstatus;
}dnb_ber_status_st;

typedef struct {
      UI_8      cmd;
      UI_16     msg_num;
      /* Bit-Encoded 1 to 7 hop neighbors of current node per byte
         Eg: byte0: 0000_0000_0000_1111 -> indicates LUID 1/2/3/4 are one Hop
         Neighbors 
       */
      //unsigned long int		nblist[7];
      unsigned long long nblist[7];
      /* Bit-Encoded values of one hop neighbors of each node in network
         Eg: for index-0, ie LUID-1: 0000_0000_0000_1110 -> indicates LUID 2/3/4 are its one Hop
         Neighbors 
       */
      FL_64     topologu[DIGI_NO_NODS];
      loc_info_t    loc_info[DIGI_NO_NODS];
      bool e_MPR;
}dnb_routing_activity_t;


typedef struct
{
    UI_8   cmd;
    UI_16  msg_num;
    UI_8   enable;
} comsec_ctrl_t;

typedef struct
{
    UI_8   cmd;
    UI_16  msg_num;
    UI_8   cfgvalue ;
} bermode_ctrl_t;

typedef struct {
      UI_8      cmd;
      UI_16     msg_num;
      UI_8      incomplete;
      UI_16     hops_per_sec;
      UI_16     nof_freqs;
      UI_32     freqs[500];
} fh_params_t;


typedef struct
{
	UI_16 hops_per_sec;
	UI_16 nof_freqs;
	UI_32 minfreqs;
   UI_32 maxfreqs;
   UI_32 freqstep;   
}fh_config_t;

typedef struct squelch_config {
    UI_8   cmd;
    UI_16  msg_num;
    UI_8 ctss_mode; /*0->disable all,1-nato,2->single tone,3- double tone*/
    UI_8 mode;  /*1-> tx , 2-> rx*/
    UI_8 value; /*1 -> enable, 0->disable*/
}squelch_config_t;

typedef union {
      Voice_Data_Arm2Dsp_st  voice_data_arm2dsp_obj;
      Voice_Data_Dsp2Arm_st  voice_data_dsp2arm_obj;
      Cmd_Data_st  cmd_data_obj;
      Rsp_Data_st  rsp_data_obj;
      Sqlch_Freq_Dev_Set_st sqlch_freq_dev_obj;
      Resp_Sqlch_Freq_Dev_Set_st resp_sqlch_freq_dev_obj;
      Sqlch_Dual_En_st sqlch_dual_en_obj;
      Resp_Sqlch_Dual_En_st resp_sqlch_dual_en_obj;
      Dsp_Sw_Ver_st dsp_sw_ver_obj;
      Resp_Dsp_Sw_Ver_st resp_dsp_sw_ver_obj;
      Dsp_Rd_st dsp_rd_obj;
      Resp_Dsp_Rd_st resp_dsp_rd_obj;
      Dsp_Wr_st dsp_wr_obj; 
      Resp_Dsp_Wr_st resp_dsp_wr_obj;
      DigitalVoiceDataPacket_st dig_voice_arm2dsp_obj;
      tx_attn_t tx_attn_obj;
      rx_gain_t rx_gain_obj; 
      autoagc_enable_t autoagc_enable_obj; 
      per_window_size_t per_window_siz_obj;
      l1stats_window_size_t liststus;
      l1statistics_t l1stats_window_size_obj;
      mac_statistics_t mac_statistcis;
      routing_statistics_t routing_statistics;
      t_pcl_pkt_stat pcl_statistics;
      nodeconfig_msg_t nodeconfig_obj; 
      gpsinfo_t gps_info;
      rssi_info_t rssi_info;
      per_info_t per_info_obj;
      gen_dsp8_cmd_t cmdwith8value_obj;
      sec_params_st sparams;
      attn_frequency_t freq_attn_obj;
      dnb_superframe_activity_t sframe_activity_obj;
      dnb_routing_activity_t  routing_activity_obj;
      heart_beat heart_beat_obj;
      comsec_ctrl_t comsec_ctrl;
      squelch_config_t squelch_config;
      waveform_change_st waveform_config_obj;
      fh_params_t fh_params;
      bermode_ctrl_t berconfig;
		dbg_st dbg_obj;
		bitconf_st bitconf_obj;
      ctrl_power_st ctrl_powe_obj;
}Payload_st; 

typedef struct {
      UI_8		cp_dp;
      UI_8		mode;
      UI_8		packet_type;
      UI_16		payload_size;
      Payload_st	payload;     
}Msg_Packet_st;

typedef struct {
	time_t ts;
	dnb_routing_activity_t  routing_activity_obj;
}Msg_routinginfo_st;


typedef struct{
	time_t ts;
	dnb_superframe_activity_t sframe_activity_obj;
}Msg_slotinfo_st;
	

typedef struct gstatus_info
{
      FL_32 c1_freq_off;
      FL_32 c2_freq_off;
      SI_32 slot_start_pos;
      FL_32 total_freq_off;
      SI_32 max_corr_value;
      FL_32 snr;
      UI_32 rx_valid_cnt;
		UI_32 broadcast_tx_count;
		UI_32 broadcast_rx_count;
		UI_32 data_tx[MAX_QOS];
		UI_32 data_rx[MAX_QOS];
      UI_32 per_window_size;
      SI_32 rx_pkts_for_per;
      SI_32 total_rx_chksum_fail;
      FL_32 PER;
      SI_32 overall_chksum_fail;      
}gstatus_info_t;


typedef struct{
      volatile UI_32   debug_flag;
      volatile UI_8    ctrl_flag;
      volatile UI_8	tone_flag;   
      volatile UI_8	dsp_state;
      volatile UI_8	rx_sqlch_status;
      volatile UI_8	rx_dual_tone_status;
      volatile UI_8	fpga_bit_major_ver;
      volatile UI_8	fpga_bit_minor_ver;
      volatile UI_8	sl_mod_sw_major_ver;
      volatile UI_8	sl_mod_sw_minor_ver;
      volatile UI_8	sl_demod_sw_major_ver;
      volatile UI_8	sl_demod_sw_minor_ver;
      volatile UI_8	l2_sw_major_ver;
      volatile UI_8	l2_sw_minor_ver;
      volatile UI_8	arm_sw_major_ver;
      volatile UI_8     arm_sw_minor_ver;
      volatile UI_8     first_time_auth;
      volatile UI_32	sig_power;
      volatile UI_32	noise_power;
      volatile SI_32	cur_rssi;
      volatile SI_32    threshold_rssi;
      volatile UI_32    pid;
      volatile UI_32	voice_rx_count;
      volatile UI_32	voice_tx_count;
      volatile UI_32	s1_assoc_freq;
      volatile UI_32	s2_assoc_freq;
      volatile UI_32	s1_detect_freq;
      volatile UI_32	s2_detect_freq;
      volatile FL_32    g_sinad; 
      volatile UI_32    mode;//digital-->3,analog fm-->0 ,analog am-ssb-->1, am-dsb-->2 
      volatile FL_32    tx_attn;
      volatile UI_32    luid;
      volatile UI_32    mpr;
      volatile unsigned long long nblist[7];
      volatile gpsinfo_t gps_info;
      volatile gstatus_info_t gstatus_info;
      volatile DigitalVoiceDataPacket_st     digital_data ;
      void(*recvMsgData);
      volatile UI_32 model_no;
      volatile UI_8  pps_lock;
      volatile UI_32 fem_gain;
      volatile FL_32 ber_avg;
      volatile UI_32 ber_rxerrbits;
      volatile UI_32 lcd_brightness;
      volatile UI_32 lcd_timeout;
		volatile UI_32 dsp_status_bite;
		volatile UI_32 test_status;
		volatile UI_32 lcd_state;
    	volatile UI_32 gps_longitude;
      volatile UI_32 gps_latitude;
      volatile UI_32 tx_freq;

}Shm_Param_st;



typedef union DSPResponsePacket_t {
    UI_8 result;
    UI_8 wv_frm;
    UI_8 sw_ver[2];
    UI_32 frequency;
    UI_32 amplitude;
    UI_32 write_buf[2];
    nodeconfig_t node_config;
    mac_statistics_t mac_statistcis;
    routing_statistics_t routing_statistics;
    t_pcl_pkt_stat pcl_statistics;
    UI_8 tx_atten;
    UI_8 rx_gain;
    UI_8 auto_agc_enable;
    UI_32 per_window;
    UI_32 l1_stats_window;
    FL_32  RSSI[SLOTS_PER_SUPERFRAME];
    //gps_info_t gps_pos_and_time;
} DSPResponsePacket_union;

typedef struct 
{
	SL_32 mtype;
	Msg_Packet_st mtext_obj;
}Msg_st;



typedef struct {
      UI_32		encTxPktCnt;
      UI_32		encRxPktCnt;
      UI_32		encNoTxPktCnt;
      UI_32		txExcessMsgCnt;
      UI_32		voicePktCaptCnt;
      UI_32		encVoicePktCnt;
 
}bose_dbg_stats;


typedef struct
{
   volatile UI_8 ptttimeout;
   volatile UI_8 pttstate;
   volatile time_t pttstarttime;	
   volatile time_t pttendtime;	  
   SI_32 adccap_fd ;
   volatile SI_8 adccapture_close;
	volatile SI_32 dbg;
	volatile SI_32 audiodump;	  
	SI_8 bermode;	 
	SI_8 berresultcnt;
	UI_32 lcd_bklight_brightness;
	UI_32 lcd_bklight_status;
}boseappctx_st;


#if 0

struct IP_ADDR_t
{
   UI_32 addr;
};

struct MAC_ID_t
{
   UI_8 macaddr[6];
};

struct VERSION_t
{
   UI_8 macaddr[3];
};

typedef struct{

      UI_32 magicnum;
      UI_32 serial_number;
      UI_32 mission_id;
      UI_32 wavefrom_id;
      UI_32 priority;
      MODEL_t model_id;
      IP_ADDR_t ip_addr;
      MAC_ID_t mac_addr;
      UI_32 luid;
      UI_32 bbctl_serial_no;
      UI_32 bbctl_model_no;
      VERSION_t dsp_vesrion;
      VERSION_t fpga_version;
      VERSION_t slmod_ver_wave0;
      VERSION_t sldemod_ver_wave0;
      VERSION_t slmod_ver_wave0;
      VERSION_t sldemod_ver_wave0;
      VERSION_t slmod_ver_wave0;
      VERSION_t sldemod_ver_wave0;
      VERSION_t slmod_ver_wave0;
      VERSION_t sldemod_ver_wave0;
      UI_32     trx_card_slno;
      UI_32     trx_card_modelno;
      UI_32     fem_rx_slno;
      UI_32     fem_rx_modelno;
      UI_32     fem_tx_slno;
      UI_32     fem_tx_modelno;
      UI_32     pa_slno;
      UI_32     pa_modelno;
      UI_32     battery_slno;
      UI_32     battery_modelno;
      UI_32     hrf_slno;
      UI_32     hrf_modelno;
      UI_32     keypad_slno;
      UI_32     keypad_modelno;
}bose_configparams;
#endif

typedef struct dspevent
{
   //e_pcl_event event;
   UI_16 arg1;
   UI_16 arg2;
}dsp_event_st;

 
enum  
{
   UNDEF = 0,
   DSP_NODE_NOT_IN_RECV = 1,
   DSP_NO_BW_RESERVE,
   DSP_RES_REALLOCATION_FAILED,
   DSP_CONSUMER_LINK_DOWN
 /* It can grow */
};

#if 0
typedef struct dsp_event {
    e_pcl_event event;
    UINT16 arg1;
    UINT16 arg2;
}t_dsp_event_st;
#endif 

#pragma pack()

void App_guinotify(SI_8 *buf);
UI_8 App_dspnotify(SI_8 *buf);
#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */
#endif /* AppCommon__include */
