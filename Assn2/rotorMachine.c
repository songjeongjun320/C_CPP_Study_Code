#include "rotorMachine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to build rotors.ini from config file
void buildIni(char *filename) {
    FILE *inputFile = fopen(filename, "r");
    if (!inputFile) {
        perror("Could not open config file");
        exit(EXIT_FAILURE);
    }

    FILE *outputFile = fopen("rotors.ini", "w");
    if (!outputFile) {
        perror("Could not open rotors.ini for writing");
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    int value;
    while (fscanf(inputFile, "%d", &value) == 1) {
        // Perform XOR encryption with value 42
        value = value ^ 42;
        // Write the encrypted value to rotors.ini
        fprintf(outputFile, "%d\n", value);
    }

    fclose(inputFile);
    fclose(outputFile);
}

// Main function to execute the program
int main(int argc, char *argv[]) {
    // Check if the command-line arguments are correct
    if (argc != 3 || strcmp(argv[1], "-i") != 0) {
        fprintf(stderr, "Usage: %s -i <config file>\n", argv[0]);
        return 1;
    }

    // Get the config file name from command-line arguments
    char *configFile = argv[2];

    // Call buildIni function to generate rotors.ini
    buildIni(configFile);

    printf("rotors.ini has been built successfully.\n");

    return 0;
}
