#include "AppCommon.h"
typedef void (*FP)(Msg_st *);
FP get_func(int);
void heartbeat(Msg_st *);
void wf_change(Msg_st *);
void slcode_download(Msg_st *);
void dspdriver_init(Msg_st *);
void dspdigital_ind(Msg_st *);
void sets1_freq(Msg_st *);
void sets2_freq(Msg_st *);
void sets1dev_freq(Msg_st *);
void sets2dev_freq(Msg_st *);
void sets1tone_amp(Msg_st *);
void sets2tone_amp(Msg_st *);
void squelch_config(Msg_st *);
void dsp_write(Msg_st *);
void dsp_read(Msg_st *);
void getl2_ver(Msg_st *);
void getfpga_ver(Msg_st *);
void getsldemod_ver(Msg_st *);
void getslmod_ver(Msg_st *);
void set_freqatten(Msg_st *);
void set_txattn(Msg_st *);
void get_txattn(Msg_st *);
void set_rxgain(Msg_st *);
void get_rxgain(Msg_st *);
void autoagc_enable(Msg_st *);
void set_perwindow(Msg_st *);
void set_l1window(Msg_st *);
void get_rssi(Msg_st *);
void get_l1stats(Msg_st *);
void get_l2stats(Msg_st *);
void get_l3stats(Msg_st *);
void get_pclstatus(Msg_st *);
void get_per(Msg_st *);
void get_gpsinfo(Msg_st *);
void get_slotinfo(Msg_st *);
void get_topology(Msg_st *);
void sec_params(Msg_st *);
void comsec_ctrl(Msg_st *);
void fh_paramas(Msg_st *);
void ber_config(Msg_st *);
void node_config(Msg_st *);


struct cmd_st{
	int cmd;
	FP fn_name; 
	};

void slot_dump(Msg_slotinfo_st *slotinfo_st,int count);
FL_32 App_berprocess(Msg_slotinfo_st *sframeinfo,dnb_ber_status_st *berstatus,int curwindow);
void topology_dump(Msg_routinginfo_st *routinfo_st,UI_32 count);
void NodeconfigParse(char *,struct node_config *);
void AudioDeInit(UI_8 );
int AudioOutInit();
int AudioInInit();
void glow_front_led(int);
void Ip_Handlerdelete();
SI_32 Ip_Handlercreate();
void App_cmdfhparamprocess(fh_params_t *);
