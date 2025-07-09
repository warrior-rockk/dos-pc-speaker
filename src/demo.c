/********************************************************************
* PC Speaker Demo
*
* 09/07/2025
* Warcom Soft. - warrior.rockk@gmail.com
********************************************************************/
#include <stdint.h>
#include <stdio.h>

#include "allegro.h"
#include "pcspeaker.h"
#include "songs.h"

int main()
{    
    //init alegro
    if (allegro_init() != 0)
        return 1;

    //set up the keyboard handler
    install_keyboard(); 

    //set a graphics mode sized 320x200
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
    
    //inits pc speaker
    pc_speaker_init(10);
    
    //load song
    pc_speaker_play_song(_title2_notes, _title2_durations, 1);

    //load logo bitmap
    BITMAP *bmp = load_bmp("res/logo.bmp", desktop_palette);
    
    //set the color palette
    set_palette(desktop_palette);

    //blit bitmap
    if (bmp)
        draw_sprite(screen, bmp, (SCREEN_W>>1) - ((bmp->w)>>1), (SCREEN_H>>1) - ((bmp->h)>>1));

    //write text
    textout_centre_ex(screen, font, "PC SPEAKER Rules!", SCREEN_W/2, 60, makecol(255,0,255), -1);
    
    textout_centre_ex(screen, font, "Press \"P\" to pause song", SCREEN_W/2, 90, makecol(255,255,255), -1);
    textout_centre_ex(screen, font, "Press \"R\" to resume song", SCREEN_W/2, 100, makecol(255,255,255), -1);
    textout_centre_ex(screen, font, "Press \"S\" to stop song", SCREEN_W/2, 110, makecol(255,255,255), -1);
    textout_centre_ex(screen, font, "Press \"SPACE\" to change song", SCREEN_W/2, 120, makecol(255,255,255), -1);

    textout_centre_ex(screen, font, "Press \"ESC\" to exit", SCREEN_W/2, 180, makecol(255,255,255), -1);

    while (!key[KEY_ESC])
    {
        if (key[KEY_P])
            pc_speaker_pause_song();
        if (key[KEY_R])
            pc_speaker_resume_song();    
        if (key[KEY_S])
            pc_speaker_stop_song();
        if (key[KEY_SPACE])
            pc_speaker_play_song(_warcom_notes, _warcom_durations, 0);
    }    

    return 0;
}
END_OF_MAIN()
