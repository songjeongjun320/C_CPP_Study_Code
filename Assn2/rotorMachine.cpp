/*
Author: Jun Song
Date: 06/19/2024
Description: Rotormachine with c++
*/

#include "rotorMachine.h"
#include <iostream>
#include <fstream>
#include <cctype>

// Build rotors.ini file from configuration file
void buildIni(const char* filename) {
    std::ifstream configFile(filename);
    if (!configFile) {
        std::cerr << "Error: Could not open configuration file." << std::endl;
        exit(1);
    }
    std::ofstream rotorsIni("rotors.ini");
    int value;
    while (configFile >> value) {
        value = value ^ 42;
        rotorsIni << value << " ";
    }
}

// Populate rotors from rotors.ini file
void buildRotors(int rotor1[28], int rotor2[28]) {
    std::ifstream rotorsIni("rotors.ini");
    if (!rotorsIni) {
        std::cerr << "Error: Rotor machine not initialized. Run with -i option and provide an appropriate configuration file." << std::endl;
        exit(1);
    }
    for (int i = 0; i < 28; ++i) {
        int value;
        rotorsIni >> value;
        rotor1[i] = value ^ 42;
    }
    for (int i = 0; i < 28; ++i) {
        int value;
        rotorsIni >> value;
        rotor2[i] = value ^ 42;
    }
}

// Rotate rotor to the right
void rotateRotorRight(int rotor[28]) {
    int last = rotor[27];
    for (int i = 27; i > 0; --i) {
        rotor[i] = rotor[i - 1];
    }
    rotor[0] = last;
}

// Rotate rotor to the left
void rotateRotorLeft(int rotor[28]) {
    int first = rotor[0];
    for (int i = 0; i < 27; ++i) {
        rotor[i] = rotor[i + 1];
    }
    rotor[27] = first;
}

// Set rotor1 to initial position
void setRotor1(int rotor[28], int rotations) {
    for (int i = 0; i < rotations; ++i) {
        rotateRotorRight(rotor);
    }
}

// Set rotor2 to initial position
void setRotor2(int rotor[28], int rotations) {
    for (int i = 0; i < rotations; ++i) {
        rotateRotorLeft(rotor);
    }
}

// Convert character to array index
int charToIndex(char convert) {
    convert = std::toupper(convert);
    if (convert == ' ') return 26;
    if (convert == '.') return 27;
    return convert - 65;
}

// Convert array index to character
char indexToChar(int convert) {
    if (convert == 26) return ' ';
    if (convert == 27) return '.';
    return convert + 65;
}

// Encrypt file
void encryptFile(std::ifstream &infile, std::ofstream &outfile, int rotor1[28], int rotor2[28]) {
    char buffer[256];
    while (infile.getline(buffer, 256)) {
        for (int i = 0; buffer[i] != '\0'; ++i) {
            char ch = buffer[i];
            if (std::isalpha(ch) || ch == ' ' || ch == '.') {
                int idx = charToIndex(ch);
                int encryptedIdx = rotor2[rotor1[idx]];
                char encryptedChar = indexToChar(encryptedIdx);
                outfile.put(encryptedChar);
                rotateRotorRight(rotor1);
                rotateRotorLeft(rotor2);
            } else {
                outfile.put(ch);
            }
        }
        outfile.put('\n');
    }
}

// Decrypt file
void decryptFile(std::ifstream &infile, std::ofstream &outfile, int rotor1[28], int rotor2[28]) {
    char buffer[256];
    while (infile.getline(buffer, 256)) {
        for (int i = 0; buffer[i] != '\0'; ++i) {
            char ch = buffer[i];
            if (std::isalpha(ch) || ch == ' ' || ch == '.') {
                int encryptedIdx = charToIndex(ch);
                int decryptedIdx;
                for (int j = 0; j < 28; ++j) {
                    if (rotor2[j] == encryptedIdx) {
                        decryptedIdx = j;
                        break;
                    }
                }
                char decryptedChar = indexToChar(rotor1[decryptedIdx]);
                outfile.put(decryptedChar);
                rotateRotorRight(rotor1);
                rotateRotorLeft(rotor2);
            } else {
                outfile.put(ch);
            }
        }
        outfile.put('\n');
    }
}
