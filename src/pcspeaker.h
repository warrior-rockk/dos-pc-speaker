#ifndef _H_PCSPEAKER_
#define _H_PCSPEAKER_
#include <stdint.h>

void pc_speaker_play_song(int8_t *notes_, uint16_t *durations_, uint8_t _loop);
void pc_speaker_stop_song();
void pc_speaker_pause_song();
void pc_speaker_resume_song();

void pc_speaker_update();

#endif