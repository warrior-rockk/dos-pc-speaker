#include <stdint.h>
#include <stdio.h>
#include <pc.h>

#include "allegro.h"

#include "songs.h"

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

int8_t *notes;
uint16_t *durations;

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

    //load song
    notes = _title_notes;
    durations = _title_durations;
    //notes = _warcom_notes;
    //durations = _warcom_durations;
    //notes = _Foxtrot_notes;
    //durations = _Foxtrot_durations;

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
