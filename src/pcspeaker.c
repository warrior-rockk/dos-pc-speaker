#include "allegro.h"
#include "pcspeaker.h"

static int music_pos = 0;
static int prev_note = 0;
static int music_state = 0;
static int music_duration = 0;

int8_t *notes;
uint16_t *durations;

//update music timer callback
static void pc_speaker_update()
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

void pc_speaker_load_song(int8_t *_notes, uint16_t *_durations)
{
    //load song
    notes = _notes;
    durations = _durations;
    //notes = _warcom_notes;
    //durations = _warcom_durations;
    //notes = _Foxtrot_notes;
    //durations = _Foxtrot_durations;
}