import argparse
import math
import mido
import os
import sys

__version__ = "1.0"

# midi conversion main function
def midi2header(_midi_path, _output_file, _verbose):
    
    # initialize vars
    files_mid = []
    tempo = 0
    ticks_per_beat = 0
    clocks_per_click = 0
    bpm = 0
    lstNotes = []
    lstDurations = []
    midi_track_name = ""

    # open/create songs file header
    output_file = open(_output_file, "w")
    # write header
    output_file.write("#include <stdint.h>\n\n")

    # append to list all .mid of given path
    for file in os.listdir(_midi_path):
        if file.endswith('.mid'):
            files_mid.append(mido.MidiFile(_midi_path + file))

    # run for midi files list
    for i,file in enumerate(files_mid):
        ticks_per_beat = file.ticks_per_beat
        
        # run for tracks on midi file
        for track in file.tracks:
            
            # print debug info of track
            if _verbose:
                print(track)

            # run for midi msg on current track
            for msg in track:
                if msg.type == 'track_name' and midi_track_name == "":
                    # get midi name of track
                    midi_track_name = msg.name
                if msg.type == 'set_tempo':
                    # get tempo
                    tempo = msg.tempo
                    # calculate bpm
                    bpm = mido.tempo2bpm(tempo)
                if msg.type == 'time_signature':
                    # get clocks per tick
                    clocks_per_click = msg.clocks_per_click
                if msg.type == 'note_on':
                    # if note on has delta time means that comes from time on silence
                    if msg.time > 0:
                        # add the silence note (0) and the duration of silence
                        lstNotes.append(0)
                        lstDurations.append(str(math.trunc(mido.tick2second(msg.time, ticks_per_beat, tempo) * 1000)))
                        # add the note
                        lstNotes.append(str(msg.note))
                    else:
                        # add the note
                        lstNotes.append(str(msg.note))
                if msg.type == 'note_off':
                    # add the duration of note (miliseconds)
                    lstDurations.append(str(math.trunc(mido.tick2second(msg.time, ticks_per_beat, tempo) * 1000)))
        
        # write track title
        output_file.write("//%s song\n" % midi_track_name)
        print("## Converting %s midi song" % midi_track_name)

        # write notes of track
        output_file.write("int8_t _%s_notes[] = {" % midi_track_name)
        for item in lstNotes:
            output_file.write(str(item) + ",")
        output_file.write("-1};\n")
        
        # write durations of each note of track
        output_file.write("uint16_t _%s_durations[] = {" % midi_track_name)
        for item in lstDurations:
            output_file.write(str(item) + ",")
        output_file.write("0};\n")

        # clear the data for next file
        lstNotes.clear()
        lstDurations.clear()
        midi_track_name = ""

    # close output file
    output_file.close()


# =================================================================================================================
def main():
    # parse cli input arguments
    parser = argparse.ArgumentParser(
        description="Converts all midi files of given path and generates a .h with array of notes and durations",
        epilog="Copyright (C) 2025 Warcom Soft. <warrior.rockk@gmail.com>",
        )
    parser.add_argument("--version", action="version", version="%(prog)s " + __version__)

    parser.add_argument("-d", "--directory", help="Path of midi files to convert")
    parser.add_argument("-o", "--output", help="header file output")
    parser.add_argument("-v", "--verbose", action=argparse.BooleanOptionalAction, help="Show info of midi converted tracks")
    args = parser.parse_args()

    # change cwd to script path
    #os.chdir(sys.path[0])

    # call to main function
    if args.directory:
        if args.output:
            midi_path = midi2header(args.directory, args.output, args.verbose)
        else:
            parser.error("Header output file not specified (-o flag)")
    else:
        # debug testing
        #args.directory = "./res/"
        #args.output = "./src/songs.h"
        #midi_path = midi2header(args.directory, args.output, args.verbose)
        parser.error("Midi path directory not specified (-d flag)")    



if __name__ == "__main__":
    main()