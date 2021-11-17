#ifndef SDR_HOST_I_IMPL_H
#define SDR_HOST_I_IMPL_H

#include "SDR_Host_base.h"
/*
typedef unsigned char             UI_8;
typedef unsigned short            UI_16;
typedef unsigned int              UI_32;
typedef unsigned long             UL_32;
typedef char                      SI_8;
typedef short                     SI_16;
typedef int                       SI_32;
typedef long                      SL_32;
typedef float                     FL_32;
typedef double                    FL_64;
typedef volatile unsigned char    V_UI_8;
typedef volatile unsigned short   V_UI_16;
typedef volatile unsigned int     V_UI_32;
typedef volatile unsigned long    V_UL_32;

typedef struct gps_info
 {
    UI_8        cmd;
    UI_16       msg_num;
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

typedef struct{
      volatile UI_32   debug_flag;
      volatile UI_8    ctrl_flag;
      volatile UI_8     tone_flag;
      volatile UI_8     dsp_state;
      volatile UI_8     rx_sqlch_status;
      volatile UI_8     rx_dual_tone_status;
      volatile UI_8     fpga_bit_major_ver;
      volatile UI_8     fpga_bit_minor_ver;
      volatile UI_8     sl_mod_sw_major_ver;
      volatile UI_8     sl_mod_sw_minor_ver;
      volatile UI_8     sl_demod_sw_major_ver;
      volatile UI_8     sl_demod_sw_minor_ver;
      volatile UI_8     l2_sw_major_ver;
      volatile UI_8     l2_sw_minor_ver;
      volatile UI_8     arm_sw_major_ver;
      volatile UI_8     arm_sw_minor_ver;
      volatile UI_8     first_time_auth;
      volatile UI_32    sig_power;
      volatile UI_32    noise_power;
      volatile SI_32    cur_rssi;
      volatile SI_32    threshold_rssi;
      volatile UI_32    pid;
      volatile UI_32    voice_rx_count;
      volatile UI_32    voice_tx_count;
      volatile UI_32    s1_assoc_freq;
      volatile UI_32    s2_assoc_freq;
      volatile UI_32    s1_detect_freq;
      volatile UI_32    s2_detect_freq;
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

*/

class SDR_Host_i : public SDR_Host_base
{
    ENABLE_LOGGING
    public:
        SDR_Host_i(const char *uuid, const char *label);
        ~SDR_Host_i();

        void constructor();

        int serviceFunction();

    protected:
};

#endif // SDR_HOST_I_IMPL_H
