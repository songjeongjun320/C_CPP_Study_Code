#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <cctype>
#include "rotorMachine.h"

int main(int argc, char* argv[]) {
    // Check for minimum required arguments
    if (argc < 3) {
        std::cerr << "Usage error: Invalid arguments" << std::endl;
        return 1;
    }

    int rotor1[28], rotor2[28];
    bool setupIni = false;
    char *configFile = nullptr;
    char *inputFile = nullptr;
    char *outputFile = nullptr;
    int r1 = 0, r2 = 0;
    bool encrypt = false, decrypt = false;

    // Parse command line arguments
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-i") == 0) {
            setupIni = true;
            configFile = argv[++i];
        } else if (strcmp(argv[i], "-e") == 0) {
            encrypt = true;
            inputFile = argv[++i];
            outputFile = argv[++i];
        } else if (strcmp(argv[i], "-d") == 0) {
            decrypt = true;
            inputFile = argv[++i];
            outputFile = argv[++i];
        } else if (strcmp(argv[i], "-r") == 0) {
            r1 = atoi(argv[++i]);
            r2 = atoi(argv[++i]);
        }
    }

    try {
        if (setupIni) {
            buildIni(configFile);
        }
        buildRotors(rotor1, rotor2);
        setRotor1(rotor1, r1);
        setRotor2(rotor2, r2);

        if (encrypt) {
            std::ifstream infile(inputFile);
            std::ofstream outfile(outputFile);
            if (!infile || !outfile) {
                throw std::runtime_error("Error: Cannot open input/output file.");
            }
            encryptFile(infile, outfile, rotor1, rotor2);
        } else if (decrypt) {
            std::ifstream infile(inputFile);
            std::ofstream outfile(outputFile);
            if (!infile || !outfile) {
                throw std::runtime_error("Error: Cannot open input/output file.");
            }
            decryptFile(infile, outfile, rotor1, rotor2);
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}

// Build the rotors.ini file from a given configuration file
void buildIni(char *filename) {
    std::ifstream configFile(filename);
    if (!configFile.is_open()) {
        throw std::runtime_error("Error: Cannot open configuration file.");
    }

    std::ofstream rotorsFile("rotors.ini");
    if (!rotorsFile.is_open()) {
        throw std::runtime_error("Error: Cannot create rotors.ini file.");
    }

    int value;
    while (configFile >> value) {
        value ^= 42;  // Encrypt the value with XOR 42
        rotorsFile << value << " ";
    }

    configFile.close();
    rotorsFile.close();
}

// Read and build the rotor arrays from the rotors.ini file
void buildRotors(int rotor1[28], int rotor2[28]) {
    std::ifstream rotorsFile("rotors.ini");
    if (!rotorsFile.is_open()) {
        throw std::runtime_error("Error: Rotor machine not initialized. Run with -i option and provide an appropriate configuration file.");
    }

    int value;
    for (int i = 0; i < 28; ++i) {
        rotorsFile >> value;
        rotor1[i] = value ^ 42;  // Decrypt the value with XOR 42
    }

    for (int i = 0; i < 28; ++i) {
        rotorsFile >> value;
        rotor2[i] = value ^ 42;  // Decrypt the value with XOR 42
    }

    rotorsFile.close();
}

// Rotate the rotor array to the right
void rotateRotorRight(int rotor[28]) {
    int last = rotor[27];
    for (int i = 27; i > 0; --i) {
        rotor[i] = rotor[i - 1];
    }
    rotor[0] = last;
}

// Rotate the rotor array to the left
void rotateRotorLeft(int rotor[28]) {
    int first = rotor[0];
    for (int i = 0; i < 27; ++i) {
        rotor[i] = rotor[i + 1];
    }
    rotor[27] = first;
}

// Set the initial position of rotor1 by rotating it to the right
void setRotor1(int rotor[28], int rotations) {
    for (int i = 0; i < rotations; ++i) {
        rotateRotorRight(rotor);
    }
}

// Set the initial position of rotor2 by rotating it to the left
void setRotor2(int rotor[28], int rotations) {
    for (int i = 0; i < rotations; ++i) {
        rotateRotorLeft(rotor);
    }
}

// Convert a character to its corresponding rotor index
int charToIndex(char convert) {
    convert = toupper(convert);
    if (convert == ' ') return 26;
    if (convert == '.') return 27;
    return convert - 'A';
}

// Convert a rotor index back to its corresponding character
char indexToChar(int convert) {
    if (convert == 26) return ' ';
    if (convert == 27) return '.';
    return static_cast<char>(convert + 'A');
}

// Encrypt the contents of infile and write to outfile
void encryptFile(std::ifstream &infile, std::ofstream &outfile, int rotor1[28], int rotor2[28]) {
    char buffer[256];
    while (infile.getline(buffer, 256)) {
        for (int i = 0; buffer[i] != '\0'; ++i) {
            int index = charToIndex(buffer[i]);
            int intermediate = rotor1[index];
            char encryptedChar = indexToChar(rotor2[intermediate]);
            outfile.put(encryptedChar);
            rotateRotorRight(rotor1);
            rotateRotorLeft(rotor2);
        }
        outfile.put('\n');
    }
}

// Decrypt the contents of infile and write to outfile
void decryptFile(std::ifstream &infile, std::ofstream &outfile, int rotor1[28], int rotor2[28]) {
    char buffer[256];
    while (infile.getline(buffer, 256)) {
        for (int i = 0; buffer[i] != '\0'; ++i) {
            int index = charToIndex(buffer[i]);
            int intermediate = rotor2[index];
            char decryptedChar = indexToChar(rotor1[intermediate]);
            outfile.put(decryptedChar);
            rotateRotorRight(rotor1);
            rotateRotorLeft(rotor2);
        }
        outfile.put('\n');
    }
}
