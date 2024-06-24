# Makefile for Rotor Machine Project

# Compiler
CC = g++

# Compiler Flags
CFLAGS = -g -Wall

# Target executable
EXE = exe

# Source files
SRCS = rotorMachine.cpp song_jun_assn3.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Build the target executable
$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXE)

# Compile rotorMachine.cpp to rotorMachine.o
rotorMachine.o: rotorMachine.cpp
	$(CC) $(CFLAGS) -c rotorMachine.cpp -o rotorMachine.o

# Compile song_jun_assn3.cpp to song_jun_assn3.o
song_jun_assn3.o: song_jun_assn3.cpp
	$(CC) $(CFLAGS) -c song_jun_assn3.cpp -o song_jun_assn3.o

# Clean the build
clean:
	rm -f $(OBJS) $(EXE)
