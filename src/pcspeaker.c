#include <pc.h>
#include <stdint.h>

#include "pcspeaker.h"

static int music_pos = 0;
static int prev_note = 0;
static int music_duration = 0;
static uint8_t loop = 0;
static uint8_t play = 0;

int8_t *notes;
uint16_t *durations;

//frequency notes 
static uint16_t freqList[] =
{
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
15,
16,
17,
18,
19,
21,
22,
23,
25,
26,
28,
29,
31,
33,
35,
37,
39,
41,
44,
46,
49,
52,
55,
58,
62,
65,
69,
73,
78,
82,
87,
92,
98,
104,
110,
117,
123,
131,
139,
147,
156,
165,
175,
185,
196,
208,
220,
233,
247,
262,
277,
294,
311,
330,
349,
370,
392,
415,
440,
466,
494,
523,
554,
587,
622,
659,
698,
740,
784,
831,
880,
932,
988,
1047,
1109,
1175,
1245,
1319,
1397,
1480,
1568,
1661,
1760,
1865,
1976,
2093,
2218,
2349,
2489,
};

//update music timer callback
void pc_speaker_update()
{
    if (play)
    {
        if (notes[music_pos] >= 0)  //not end of song
        {
            //check note
            if (notes[music_pos] > 0)   //if note <> silence
            {
                if (notes[music_pos] != prev_note)
                {
                    sound(freqList[notes[music_pos]]);               
                    prev_note = notes[music_pos];
                }            
            }
            else
            {
                //silence
                nosound();
                prev_note = notes[music_pos];
            }

            //check duration
            if (music_duration >= durations[music_pos])
                {
                    music_pos++;
                    if (notes[music_pos] == prev_note)
                    {
                        nosound();
                        prev_note = 0;
                    }
                    //prev_note = notes[music_pos];
                    music_duration = 0;
                }
                else
                    music_duration += 10; //50ms each tick
        }
        else
        {
            //end of song
            nosound(); 
            //check loop
            if (loop)
            {
                //reset song
                music_pos = 0;
                prev_note = 0;
                music_duration = 0;   
            }
        }
    }
    else
        nosound();
}

void pc_speaker_play_song(int8_t *_notes, uint16_t *_durations, uint8_t _loop)
{
    //load song
    notes = _notes;
    durations = _durations;
    
    music_pos = 0;
    prev_note = 0;
    music_duration = 0;

    loop = _loop;
    play = 1;    
}

void pc_speaker_stop_song()
{
    nosound();
    play = 0;
    music_pos = 0;
    prev_note = 0;
    music_duration = 0;
}

void pc_speaker_pause_song()
{
    nosound();
    play = 0;    
}

void pc_speaker_resume_song()
{
    play = 1;    
}