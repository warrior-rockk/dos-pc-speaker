/********************************************************************
* PC-Speaker Allegro DOS Driver
*
* 09/07/2025
* Warcom Soft. - warrior.rockk@gmail.com
********************************************************************/

#ifndef _H_PCSPEAKER_
#define _H_PCSPEAKER_
#include <stdint.h>

//inits the pc speaker interrupt (timeResolution on ms)
void pc_speaker_init(long timeResolution);
//plays song on pc speaker (loops n times or 0: infinite)
void pc_speaker_play_song(int8_t *notes_, uint16_t *durations_, uint8_t _loop);
//stops song on pc speaker
void pc_speaker_stop_song();
//pauses song on pc speaker
void pc_speaker_pause_song();
//resumens song paused on pc speaker
void pc_speaker_resume_song();

#endif