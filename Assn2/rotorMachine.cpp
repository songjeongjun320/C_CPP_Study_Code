/*
Author: Jun Song
Date: 06/19/2024
Description: Rotormachine with c++
*/

#include "rotorMachine.h"
#include <cstdlib>
#include <cstring>

void buildIni(char *filename) {
    FILE *configFile = fopen(filename, "r");
    if (configFile == NULL) {
        fprintf(stderr, "Error: Configuration file %s not found.\n", filename);
        exit(EXIT_FAILURE);
    }

    FILE *rotorsFile = fopen("rotors.ini", "w");
    if (rotorsFile == NULL) {
        perror("Error creating rotors.ini file");
        fclose(configFile);
        exit(EXIT_FAILURE);
    }

    int value;
    while (fscanf(configFile, "%d", &value) == 1) {
        value ^= 42;
        fprintf(rotorsFile, "%d ", value);
    }

    fclose(configFile);
    fclose(rotorsFile);
}

void buildRotors(int rotor1[28], int rotor2[28]) {
    FILE *rotorsFile = fopen("rotors.ini", "r");
    if (rotorsFile == NULL) {
        fprintf(stderr, "Error: Rotor machine not initialized. Run with -i option and provide an appropriate configuration file.\n");
        exit(EXIT_FAILURE);
    }

    int value;
    for (int i = 0; i < 28; ++i) {
        fscanf(rotorsFile, "%d", &value);
        rotor1[i] = value ^ 42;
    }

    for (int i = 0; i < 28; ++i) {
        fscanf(rotorsFile, "%d", &value);
        rotor2[i] = value ^ 42;
    }

    fclose(rotorsFile);
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
    if (convert >= 'A' && convert <= 'Z') {
        return convert - 'A';
    } else if (convert == ' ') {
        return 26;
    } else if (convert == '.') {
        return 27;
    } else {
        fprintf(stderr, "Error: Invalid character %c\n", convert);
        exit(EXIT_FAILURE);
    }
}

char indexToChar(int convert) {
    if (convert >= 0 && convert <= 25) {
        return static_cast<char>(convert + 'A');
    } else if (convert == 26) {
        return ' ';
    } else if (convert == 27) {
        return '.';
    } else {
        fprintf(stderr, "Error: Invalid index %d\n", convert);
        exit(EXIT_FAILURE);
    }
}

void encryptFile(FILE* infile, FILE* outfile, int rotor1[28], int rotor2[28]) {
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), infile)) {
        for (size_t i = 0; i < strlen(buffer); i++) {
            if (buffer[i] != '\n') {
                int idx = charToIndex(buffer[i]);
                int encryptedIdx = rotor2[rotor1[idx]];
                buffer[i] = indexToChar(encryptedIdx);
                rotateRotorRight(rotor1);
                rotateRotorLeft(rotor2);
            }
        }
        fputs(buffer, outfile);
    }
}

void decryptFile(FILE* infile, FILE* outfile, int rotor1[28], int rotor2[28]) {
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), infile)) {
        for (size_t i = 0; i < strlen(buffer); i++) {
            if (buffer[i] != '\n') {
                int idx = charToIndex(buffer[i]);
                int decryptedIdx = rotor1[rotor2[idx]];
                buffer[i] = indexToChar(decryptedIdx);
                rotateRotorRight(rotor1);
                rotateRotorLeft(rotor2);
            }
        }
        fputs(buffer, outfile);
    }
}