# Author: Jun Song
# Date: 06/19/2024
# Description: Rotormachine with C++

# Makefile for Rotor Machine Project

# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11

# Target executable
TARGET = rotorMachine

# Source files
SRC = song_jun_assn3.cpp rotorMachine.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Build the target executable
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp rotorMachine.h
	$(CXX) $(CXXFLAGS) -c $<

# Clean the build
clean:
	rm -f $(OBJ) $(TARGET)
