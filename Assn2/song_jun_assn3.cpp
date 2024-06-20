/*
Author: Jun Song
Date: 06/19/2024
Description: Rotormachine with c++
*/

#include "rotorMachine.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

void printUsage() {
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "./exe -i <file>\n");
    fprintf(stderr, "./exe -e <file1> <file2> -r <r1> <r2>\n");
    fprintf(stderr, "./exe -d <file1> <file2> -r <r1> <r2>\n");
    fprintf(stderr, "./exe -e <file1> <file2> -r <r1> <r2> -i <file>\n");
    fprintf(stderr, "./exe -d <file1> <file2> -r <r1> <r2> -i <file>\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
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
        int rotor1Pos = atoi(argv[5]);
        int rotor2Pos = atoi(argv[6]);

        if (argc == 8) {
            if (strcmp(argv[7], "-i") == 0) {
                buildIni(argv[8]);
            } else {
                printUsage();
            }
        }

        ifstream infile(inputFile);
        if (!infile.is_open()) {
            perror("Error opening input file");
            exit(EXIT_FAILURE);
        }

        ofstream outfile(outputFile);
        if (!outfile.is_open()) {
            perror("Error opening output file");
            infile.close();
            exit(EXIT_FAILURE);
        }

        int rotor1[28], rotor2[28];
        buildRotors(rotor1, rotor2);
        setRotor1(rotor1, rotor1Pos);
        setRotor2(rotor2, rotor2Pos);

        if (strcmp(argv[1], "-e") == 0) {
            encryptFile(infile, outfile, rotor1, rotor2);
        } else {
            decryptFile(infile, outfile, rotor1, rotor2);
        }

        infile.close();
        outfile.close();
    } else {
        printUsage();
    }

    return 0;
}
