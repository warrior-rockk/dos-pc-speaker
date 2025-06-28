import math
import mido
import os
import sys

files_mid = []
files_txt = []

# info vars
tempo = 0
ticks_per_beat = 0
clocks_per_click = 0
bpm = 0
lstNotes = []
lstDurations = []
midi_name = ""

# change cwd to script path
os.chdir(sys.path[0])

for file in os.listdir(os.getcwd()):
    if file.endswith('.mid'):
        files_mid.append(mido.MidiFile(file))
        files_txt.append(open(file.split('.')[0]+'.txt','w'))

for i,file in enumerate(files_mid):
    output = ''
    ticks_per_beat = file.ticks_per_beat
    
    for track in file.tracks:
        # debug info of track
        print(track)
        
        for msg in track:
            if msg.type == 'track_name' and midi_name == "":
                midi_name = msg.name
            if msg.type == 'set_tempo':
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
    
    # Print notes
    files_txt[i].write("int8_t _%s_notes[] = {" % midi_name)
    for item in lstNotes:
        files_txt[i].write(str(item) + ",")
    files_txt[i].write("-1};\n")
    
    # Print durations
    files_txt[i].write("uint16_t _%s_durations[] = {" % midi_name)
    for item in lstDurations:
        files_txt[i].write(str(item) + ",")
    files_txt[i].write("0};")

    files_txt[i].close()

    # clear the data for next file
    lstNotes.clear()
    lstDurations.clear()
    midi_name = ""