#ifndef _H_PCSPEAKER_
#define _H_PCSPEAKER_
#include <stdint.h>

void pc_speaker_update();
void pc_speaker_load_song(int8_t *notes_, uint16_t *durations_);
void pc_speaker_update();

#endif