#define PCM_DEVICE      "default"    
#define MSG_TYPE_PLAY   88

UI_8 AudioInRead(SI_16 *pcminbuf,SI_32 framesize);
void AudioOutWrite (SI_16 *buff , SI_32 framelen);
int AudioInInit() ;
void AudioCpatureStart();
int AudioOutInit() ;
void AudioDeInit(UI_8 interface);
void *AudioCaptureHandler();
void Unmute_Mic();
void Mute_Mic();
void Unmute_Spkr();
void Mute_Spkr();
