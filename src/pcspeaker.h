#ifndef _H_PCSPEAKER_
#define _H_PCSPEAKER_

#include <stdint.h>

//frequncy notes 
uint16_t freqList[] =
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


static void pc_speaker_update();
void pc_speaker_load_song(int8_t *notes_, uint16_t *durations_);


//update music timer callback
static void pc_speaker_update_callback()
{
    pc_speaker_update();
}
END_OF_FUNCTION(pc_speaker_update_callback);



#endif