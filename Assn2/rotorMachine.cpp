/*
Author: Jun Song
Date: 06/19/2024
Description: Rotormachine with c++
*/

#include "rotorMachine.h"
#include <fstream>
#include <iostream>

using namespace std;

void buildIni(char *filename) {
    ifstream configFile(filename);
    if (!configFile.is_open()) {
        cerr << "Error: Unable to open configuration file " << filename << endl;
        exit(EXIT_FAILURE);
    }

    ofstream rotorsFile("rotors.ini");
    if (!rotorsFile.is_open()) {
        cerr << "Error: Unable to create or open rotors.ini" << endl;
        configFile.close();
        exit(EXIT_FAILURE);
    }

    int value;
    while (configFile >> value) {
        value ^= 42;  // XOR encryption with 42
        rotorsFile << value << " ";
    }

    configFile.close();
    rotorsFile.close();
}

void buildRotors(int rotor1[28], int rotor2[28]) {
    ifstream rotorsFile("rotors.ini");
    if (!rotorsFile.is_open()) {
        cerr << "Error: Rotor machine not initialized. Run with -i option and provide an appropriate configuration file." << endl;
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 28; ++i) {
        rotorsFile >> rotor1[i];
    }
    for (int i = 0; i < 28; ++i) {
        rotorsFile >> rotor2[i];
    }

    rotorsFile.close();
}

void rotateRotorRight(int rotor[28]) {
    int temp = rotor[27];
    for (int i = 27; i > 0; --i) {
        rotor[i] = rotor[i - 1];
    }
    rotor[0] = temp;
}

void rotateRotorLeft(int rotor[28]) {
    int temp = rotor[0];
    for (int i = 0; i < 27; ++i) {
        rotor[i] = rotor[i + 1];
    }
    rotor[27] = temp;
}

void setRotor1(int rotor[28], int rotations) {
    for (int i = 0; i < rotations; ++i) {
        rotateRotorRight(rotor);
    }
}

void setRotor2(int rotor[28], int rotations) {
    for (int i = 0; i < rotations; ++i) {
        rotateRotorLeft(rotor);
    }
}

int charToIndex(char convert) {
    if (convert == ' ') {
        return 26;
    } else if (convert == '.') {
        return 27;
    } else {
        return toupper(convert) - 'A';
    }
}

char indexToChar(int convert) {
    if (convert == 26) {
        return ' ';
    } else if (convert == 27) {
        return '.';
    } else {
        return static_cast<char>(convert + 'A');
    }
}

void encryptFile(ifstream &infile, ofstream &outfile, int rotor1[28], int rotor2[28]) {
    int ch;
    while ((ch = infile.get()) != EOF) {
        if (ch == '\n') {
            outfile.put('\n');
            continue;
        }
        int index = charToIndex(static_cast<char>(ch));
        int encryptedIndex = rotor2[rotor1[index]];
        char encryptedChar = indexToChar(encryptedIndex);
        outfile.put(encryptedChar);
        rotateRotorRight(rotor1);
        rotateRotorLeft(rotor2);
    }
}

void decryptFile(ifstream &infile, ofstream &outfile, int rotor1[28], int rotor2[28]) {
    int ch;
    while ((ch = infile.get()) != EOF) {
        if (ch == '\n') {
            outfile.put('\n');
            continue;
        }
        int index = charToIndex(static_cast<char>(ch));
        // Find original index from rotor2
        for (int i = 0; i < 28; ++i) {
            if (rotor2[i] == index) {
                index = i;
                break;
            }
        }
        int decryptedIndex = rotor1[index];
        char decryptedChar = indexToChar(decryptedIndex);
        outfile.put(decryptedChar);
        rotateRotorRight(rotor1);
        rotateRotorLeft(rotor2);
    }
}
