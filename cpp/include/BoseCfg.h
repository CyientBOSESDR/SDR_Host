
#ifndef __BOSECFG_H_
#define __BOSECFG_H_

#include "SDR_BITE_Std.h"

typedef struct IP_ADDR
{
   UI_8 addr[4];
}IP_ADDR_t;

typedef struct MAC_ID_t
{
   UI_8 macaddr[6];
}MAC_ID_t;

typedef struct VERSION
{
   UI_8 version[4];
}VERSION_t;
#pragma pack(1)
typedef struct
{
   UI_32 magicnum;
   UI_32 serial_number;
   UI_32 mission_id;
   UI_32 wavefrom_id;
   UI_32 priority;
   UI_32 model_id;
   IP_ADDR_t ip_addr;
   UI_32 luid;
   UI_32 bbctl_serial_no;
   UI_32 bbctl_model_no;
   VERSION_t dsp_vesrion;
   VERSION_t fpga_version;
   VERSION_t slmod_ver_wave0;
   VERSION_t sldemod_ver_wave0;
   VERSION_t slmod_ver_wave1;
   VERSION_t sldemod_ver_wave1;
   VERSION_t slmod_ver_wave2;
   VERSION_t sldemod_ver_wave2;
   VERSION_t slmod_ver_wave3;
   VERSION_t sldemod_ver_wave3;
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
   UI_32 strid;
   MAC_ID_t  mac_addr;
	UI_16 dummy;
   UI_32 pttontme;
   UI_32 pttoffmfact;
	UI_32 lcd_brightness;
	UI_32 lcd_timeout;
	UI_32 chk_sum;

}bose_configparams;
#pragma pack()
enum Config_Type
{
   CONFIG_MAGICNUM_ID   = 255,
   CONFIG_SNO_ID   = 0X1,
   CONFIG_MISSION_ID,
   CONFIG_WAVEFROM_ID,
   CONFIG_PRIORITY,
   CONFIG_MODEL_ID,
   CONFIG_IP_ADDR,
   CONFIG_LUID_ID,

   CONFIG_BBCTLSINO_ID,
   CONFIG_BBCTLMODNO_ID,
   CONFIG_DSPVER_ID,
   CONFIG_FPGAVER_ID,
   CONFIG_SLMODWAVE0_ID,
   CONFIG_SLDMODWAVE0VER_ID,

   CONFIG_SLMODWAVE1_ID,
   CONFIG_SLDMODWAVE1VER_ID,

   CONFIG_SLMODWAVE2_ID,
   CONFIG_SLDMODWAVE2VER_ID,

   CONFIG_SLMODWAVE3_ID,
   CONFIG_SLDMODWAVE3VER_ID,


   CONFIG_TRXCARDSLNO_ID,
   CONFIG_TRXCARDMODEL_ID,
   CONFIG_FEMRXSLNO_ID,
   CONFIG_FEMRXMODEL_ID,
   CONFIG_FEMTXSLLNO_ID,
   CONFIG_FEMTXMODEL_ID,
   CONFIG_PASLNO_ID,
   CONFIG_PAMODELNO_ID,

   CONFIG_BATTERYSLNO_ID,
   CONFIG_BATTERYMODL_ID,

   CONFIG_HRFSLNO_ID,
   CONFIG_HRFMODEL_ID,

   CONFIG_KEYBRDSLNO_ID,
   CONFIG_KEYBRDMODEL_ID,
   CONFIG_STRINGID_ID,
   CONFIG_MAC_ADDR,
   CONFIG_PTTONTME_ID,
   CONFIG_PTTOFFMFACT_ID,
	CONFIG_LCD_BRIGHTNESS_ID,
	CONFIG_LCD_TIMEOUT_ID,
	CONFIG_CHK_SUM
	
 
};
SI_8 AppEepromRd(SI_16 addr,SI_8 *data,SI_32 size);
SI_8 AppEepromWr(SI_16 addr,SI_8 *data,SI_32 size);

#endif /* __BOSECFG_H_ */
