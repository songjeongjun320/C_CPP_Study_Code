#include "rotorMachine.h" // Include the header file for rotor machine functions
#include <cstdio> // Include C standard I/O functions
#include <cstdlib> // Include C standard library functions
#include <cstring> // Include C string manipulation functions
#include <iostream> // Include input/output stream functions
#include <fstream> // Include file stream functions

using namespace std;

/**
 * @brief Prints usage instructions for the program.
 */
void printUsage() {
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "./exe -i <file>\n");
    fprintf(stderr, "./exe -e <file1> <file2> -r <r1> <r2>\n");
    fprintf(stderr, "./exe -d <file1> <file2> -r <r1> <r2>\n");
    fprintf(stderr, "./exe -e <file1> <file2> -r <r1> <r2> -i <file>\n");
    fprintf(stderr, "./exe -d <file1> <file2> -r <r1> <r2> -i <file>\n");
    exit(EXIT_FAILURE);
}

/**
 * @brief Main function that handles command line arguments and orchestrates the encryption/decryption process.
 * @param argc Number of command line arguments.
 * @param argv Array of command line argument strings.
 * @return Exit status of the program.
 */
int main(int argc, char *argv[]) {
    // Check if there are enough command line arguments
    if (argc < 3) {
        printUsage();
    }

    // Handle the case when initializing rotor configurations
    if (strcmp(argv[1], "-i") == 0) {
        if (argc != 3) {
            printUsage();
        }
        buildIni(argv[2]);

    // Handle encryption or decryption cases
    } else if ((strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "-d") == 0)) {
        bool withIni = false;
        char *iniFile = nullptr;

        // Check the correct number and format of command line arguments
        if ((argc != 7 && argc != 9) || (strcmp(argv[4], "-r") != 0) || (argc == 9 && strcmp(argv[7], "-i") != 0)) {
            printUsage();
        }

        // Check if an initialization file is specified
        if (argc == 9) {
            withIni = true;
            iniFile = argv[8];
        }
        
        // If an initialization file is provided, build rotors from it
        if (withIni) {
            buildIni(iniFile);
        }

        char *inputFile = argv[2];
        char *outputFile = argv[3];
        int rotor1Pos = atoi(argv[5]);
        int rotor2Pos = atoi(argv[6]);

        // Build rotors and set their initial positions
        int rotor1[28], rotor2[28];
        buildRotors(rotor1, rotor2);
        setRotor1(rotor1, rotor1Pos);
        setRotor2(rotor2, rotor2Pos);
        cout << "Rotor 1: ";
        for (int i = 0; i < 28; ++i) {
            cout << rotor1[i] << " ";
        }
        cout << endl;
        cout << "Rotor 2: ";
        for (int i = 0; i < 28; ++i) {
            cout << rotor2[i] << " ";
        }
        cout << endl;

        // Open input file for reading
        ifstream infile(inputFile);
        if (!infile.is_open()) {
            perror("Error opening input file");
            exit(EXIT_FAILURE);
        }

        // Open output file for writing
        ofstream outfile(outputFile);
        if (!outfile.is_open()) {
            perror("Error opening output file");
            infile.close();
            exit(EXIT_FAILURE);
        }

        // Encrypt or decrypt the input file and write to the output file
        if (strcmp(argv[1], "-e") == 0) {
            encryptFile(infile, outfile, rotor1, rotor2);
        } else {
            decryptFile(infile, outfile, rotor1, rotor2);
        }

        // Close files after processing
        infile.close();
        outfile.close();

    // Handle invalid command line arguments
    } else {
        printUsage();
    }

    return 0; // Return 0 to indicate successful execution
}
