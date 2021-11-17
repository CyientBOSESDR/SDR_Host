/**
 *  \file   sl_code_download.h
 *
 *  \brief  SL Code download I2C client driver
 *
 */

/* local header files */
#include <SDR_Std.h>


#define  SL_FWMOD_FM         "/home/root/bose_fm_mod.bin"
#define  SL_FWDEMOD_FM       "/home/root/bose_fm_demod.bin" 

#define  SL_FWMOD_DNB        "/home/root/bose_dnb_mod.bin"
#define  SL_FWDEMOD_DNB     "/home/root/bose_dnb_demod.bin"
        
#define  SL_FWMOD_AMDSB      "/home/root/bose_dsb_mod.bin"
#define  SL_FWDEMOD_AMDSB    "/home/root/bose_dsb_demod.bin"

#define  SL_FWMOD_AMSSB      "/home/root/bose_ssb_mod.bin"
#define  SL_FWDEMOD_AMSSB    "/home/root/bose_ssb_demod.bin"

#define  SL_FWMOD_DWB        "/home/root/bose_dwb_mod.bin"
#define  SL_FWDEMOD_DWB      "/home/root/bose_dwb_demod.bin"

/* Driver macros */
#define SL_CODE_DW_SUCCESS 0x0
#define SL_CODE_DW_FAILED 0x1
#define I2C_STS_SUCCESS 0x0

/* TODO: Define I2C slave address */
#define SL_MOD_I2C_SLAVE_ADDR 0x40
#define SL_DEMOD_I2C_SLAVE_ADDR 0x60

/* TODO: Define values for these macros */
/* SL MOD/DEMOD Register address */
#define PRUTHVI_STATUS_REG_ADDR 0x84
#define PRUTHVI_RX_FIFO_REG_ADDR 0x0
#define PRUTHVI_TX_FIFO_REG_ADDR 0x80
#define DEMOD_BOOT_STATUS 0x6080
#define SET_DSP_RESET_ADDR 0x6054
#define DSP_RESET 0x0001
#define DSP_RESET_RELEASE 0x0000

typedef enum
{
	eFM,
	eAM_SSB,
	eAM_DSB,
   eNB_CPFSK,
   eWB_CPFSK
}SL_SDR_Waveforms_enum;

/* Module name used in messages */
#define SL_CODE_DOWNLOAD "SL_CODE_DOWNLOAD"
#define MAX_I2C_BUFF_SIZE 64

void SL_mod_config_over_I2C();
void SL_demod_config_over_I2C();
void SL_config_over_I2C();
uint32_t SL90xx_Memory_Read(uint16_t I2cAddress, uint32_t address);
void slCodeDownloadmain(UI_8 mode);
