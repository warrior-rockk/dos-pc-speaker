# DOS PC Speaker driver to play music on pc speaker

## How it works

This simple library allows to play monophonic music on pc speaker.
It uses Allegro game library to manage time interrupt.

The functions are self explanatory on the header file.

Includes a script tool on python to convert midi notes from midi tracks to the header file *songs.h* needed to read the notes and durations of song.

## Compile the demo

To compile the demo run `make debug` or `make release` and launch dosbox on build directory