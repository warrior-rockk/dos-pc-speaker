#include <stdint.h>
#include <stdio.h>
#include <pc.h>

#include "allegro.h"

int music_pos = 0;
int prev_note = 0;
int music_state = 0;
int music_duration = 0;

//test export
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

//int8_t notes[] = {0,64,64,64,0,60,64,0,64,0,60,64,65,67,65,0,62,62,0,65,0,64,62,0,60,0,56,0,60,63,62,0,64,64,64,64,60,64,0,64,64,60,64,65,67,65,0,62,62,62,65,65,64,62,0,60,0,56,0,60,63,62,-1};
//uint16_t durations[] = {500,250,250,375,125,250,250,125,500,125,250,250,250,500,625,125,250,1625,125,375,125,250,375,125,2750,125,250,125,250,500,4000,428,214,214,321,107,214,214,107,107,428,214,214,214,428,535,107,214,1392,107,321,107,214,321,107,2357,107,214,107,214,428,3428,0};

int8_t notes[] = {55,55,60,60,64,64,67,67,66,66,64,64,60,60,55,55,57,57,62,62,66,66,69,69,68,68,66,66,62,62,57,57,59,59,64,64,68,68,71,71,64,64,68,68,71,71,64,64,68,68,71,71,-1};
uint16_t durations[] = {0,250,0,250,0,250,0,250,0,250,0,250,0,250,0,250,0,250,0,250,0,250,0,250,0,250,0,250,0,250,0,250,0,250,0,250,0,250,0,500,0,250,0,250,0,250,250,250,0,250,0,500,0};

//update music timer callback
static void update_music(void)
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
        //end of song
        nosound();    
}
END_OF_FUNCTION(update_music);

int main()
{    
    /* you should always do this at the start of Allegro programs */
    if (allegro_init() != 0)
        return 1;

    /* set up the keyboard handler */
    install_keyboard(); 

    /* set a graphics mode sized 320x200 */
    if (set_gfx_mode(GFX_AUTODETECT, 320, 200, 0, 0) != 0) 
    {
        if (set_gfx_mode(GFX_SAFE, 320, 200, 0, 0) != 0) 
        {
            set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
            allegro_message("Unable to set any graphic mode\n%s\n", allegro_error);
            return 1;
        }
    }

    //install timer interrupt
    install_timer();
    LOCK_FUNCTION(update_music);
    install_int(update_music, 10);   //50ms

    /* load bitmap */
    BITMAP *bmp = load_bmp("res/logo.bmp", desktop_palette);
    
    /* set the color palette */
    set_palette(desktop_palette);

    /* clear the screen to white */
    clear_to_color(screen, 0);
    
    /* blit bitmap*/
    if (bmp)
        draw_sprite(screen, bmp, (SCREEN_W>>1) - ((bmp->w)>>1), (SCREEN_H>>1) - ((bmp->h)>>1));

    /* you don't need to do this, but on some platforms (eg. Windows) things
    * will be drawn more quickly if you always acquire the screen before
    * trying to draw onto it.
    */
    acquire_screen();

    /* write some text to the screen with black letters and transparent background */
    textout_centre_ex(screen, font, "Hello, world from DOS!", SCREEN_W/2, SCREEN_H/2, makecol(255,255,255), -1);

    /* you must always release bitmaps before calling any input functions */
    release_screen();

    

    /* wait for a key press */
    readkey();

    

    return 0;
}
END_OF_MAIN()
