import math
import mido
import os
import sys

files_mid = []

# initialize vars
tempo = 0
ticks_per_beat = 0
clocks_per_click = 0
bpm = 0
lstNotes = []
lstDurations = []
midi_name = ""

# change cwd to script path
os.chdir(sys.path[0])

# open/create songs file header
output_file = open(os.getcwd() + "/../src/songs.h", "w")
# write header
output_file.write("#include <stdint.h>\n\n")

# append to list all .mid files on current script dir
for file in os.listdir(os.getcwd()):
    if file.endswith('.mid'):
        files_mid.append(mido.MidiFile(file))

# run for midi files list
for i,file in enumerate(files_mid):
    ticks_per_beat = file.ticks_per_beat
    
	# run for tracks on midi file
    for track in file.tracks:
        
		# print debug info of track
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