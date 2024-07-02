/*
Name: Jun Song
Date: 07/01/2024
Description: This program simulates a zombie conga line using a templated doubly-linked list.
Usage:
    Compile the program using the provided Makefile:
        make
    Run the executable:
        ./exe
    This will generate a conga line of zombies with random types, adding them either to the front or the end of the list.
*/

# Define object files and executable
OBJS = hw_song_jun.o zombie_song.o
EXE = exe

# Compiler options
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)  # Compiler flags for compiling individual files
LFLAG = -Wall $(DEBUG)       # Linker flags for linking object files

# Rule to build executable
$(EXE): $(OBJS)
	$(CC) $(LFLAG) $(OBJS) -o $(EXE)

# Rule to compile hw_song_jun.o
hw_song_jun.o: hw_song_jun.cpp linkedlist_song.hpp zombie_song.h
	$(CC) $(CFLAGS) hw_song_jun.cpp

# Rule to compile zombie_song.o
zombie_song.o: zombie_song.cpp zombie_song.h
	$(CC) $(CFLAGS) zombie_song.cpp

# Clean rule to remove object files and executable
clean:
	rm -f *.o $(EXE)
