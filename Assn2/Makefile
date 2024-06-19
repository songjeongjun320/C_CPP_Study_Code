# Author: Jun Song
# Date: 06/19/2024
# Description: Rotormachine with c++


# Makefile for Rotor Machine Project

# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11

# Target executable
TARGET = rotorMachine

# Source files
SRC = assn3.cpp rotor.cpp

# Header files
HDR = rotorMachine.h

# Object files
OBJ = $(SRC:.cpp=.o)

# Build the target executable
all: $(TARGET)

$(TARGET): $(OBJ)
    $(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp $(HDR)
    $(CXX) $(CXXFLAGS) -c $<

# Clean the build
clean:
    rm -f $(OBJ) $(TARGET)
