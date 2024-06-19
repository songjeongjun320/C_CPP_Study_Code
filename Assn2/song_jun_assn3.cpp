/*
Author: Jun Song
Date: 06/19/2024
Description: Rotormachine with c++
*/

// assn3.cpp

#include "rotorMachine.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

void printUsage() {
    std::cerr << "Usage:\n";
    std::cerr << "./exe -i <file>\n";
    std::cerr << "./exe -e <file1> <file2> -r <r1> <r2>\n";
    std::cerr << "./exe -d <file1> <file2> -r <r1> <r2>\n";
    std::cerr << "./exe -e <file1> <file2> -r <r1> <r2> -i <file>\n";
    std::cerr << "./exe -d <file1> <file2> -r <r1> <r2> -i <file>\n";
    exit(1);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printUsage();
    }

    if (strcmp(argv[1], "-i") == 0) {
        if (argc != 3) {
            printUsage();
        }
        buildIni(argv[2]);
    } else if (strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "-d") == 0) {
        if (argc != 6 && argc != 8) {
            printUsage();
        }

        char *inputFile = argv[2];
        char *outputFile = argv[3];
        int rotations1 = atoi(argv[5]);
        int rotations2 = atoi(argv[6]);

        if (argc == 8 && strcmp(argv[7], "-i") == 0) {
            buildIni(argv[8]);
        }

        int rotor1[28], rotor2[28];
        buildRotors(rotor1, rotor2);
        setRotor1(rotor1, rotations1);
        setRotor2(rotor2, rotations2);

        std::ifstream infile(inputFile);
        std::ofstream outfile(outputFile);

        if (!infile) {
            std::cerr << "Error: Could not open input file." << std::endl;
            return 1;
        }
        if (!outfile) {
            std::cerr << "Error: Could not open output file." << std::endl;
            return 1;
        }

        if (strcmp(argv[1], "-e") == 0) {
            encryptFile(infile, outfile, rotor1, rotor2);
        } else {
            decryptFile(infile, outfile, rotor1, rotor2);
        }
    } else {
        printUsage();
    }

    return 0;
}
