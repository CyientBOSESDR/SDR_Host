/******************************************************************************
 * FILE NAME: SDR_BOSE_App.h                                                  *
 *                                                                            *
 * PURPOSE: This header file consists declarations of CYIENT proprietary      *
 *          functions and variables used for SDR Application.                 *
 *                                                                            *
 * GLOBAL VARIABLES:                                                          *
 *                                                                            *
 * Variable                 Type                Description                   *
 *                                              link list.                    *
 * DEVELOPMENT/ CHANGE HISTORY:                                               *
 *                                                                            *
 * Date       Author            Release         Description Of Change         *
 * 01/10/17   Vishal Badole      1.0.0          None                          *
 *                                                                            *
 *                                                                            *
 *****************************************************************************/

#ifndef _SDR_BOSE_APP_H_
#define _SDR_BOSE_APP_H_

#include <alsa/asoundlib.h>
#include <SDR_Std.h>
#include <AppCommon.h>

#pragma pack(1)
typedef struct {
   SI_8 squelch;
   SI_16 ctss_tone_freq;
} Sqlch_Data_st;

#pragma pack()


/*SI_32 InitAlsaParam (snd_pcm_t **loc_handle_ptr, const SI_8 *loc_device_name_ptr
      , SI_32 loc_func_mode, UI_32 loc_rate, UI_32 loc_format, 
      UL_32 loc_frame_size);*/

int InitAlsaParam(snd_pcm_t **loc_handle_ptr,  const char * loc_device_name_ptr, 
      int loc_func_mode, unsigned int loc_rate, snd_pcm_format_t  loc_format, 
      snd_pcm_uframes_t loc_frame_size);

SI_32 InitVoicePacktData(Voice_Data_Arm2Dsp_st *loc_voice_data_ptr,
      SI_8 loc_switch_id, SI_8 loc_path_id,
      SI_8 loc_data_ptr[], SI_16 loc_payload_size);

SI_32 InitCmdPacktData (Cmd_Data_st *loc_cmd_data_ptr, UI_8 loc_cmd, 
      UI_16 loc_msg_num, UI_16 loc_test_id);

SI_32 InitMsgPacktData (Msg_Packet_st *loc_msg_data_ptr, UI_8 loc_plane, 
      UI_8 loc_mode, UI_8 loc_packt_type, 
      UI_16 loc_payload_size);

SI_32 RunCbitTest (void);

Shm_Param_st *AllocSharedMemory(key_t loc_shm_key, SI_32 loc_shm_size);

SI_32 mbit_test (void);

#endif
