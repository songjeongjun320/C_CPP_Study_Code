/*
Author: Jun Song
Date: 06/19/2024
Description: Rotormachine with c++
*/

#include "rotorMachine.h" // Include the header file for rotor machine functions
#include <fstream> // Include file stream for file operations
#include <iostream> // Include input/output stream functions

using namespace std;

/**
 * @brief Reads a configuration file and encrypts its contents using XOR encryption with 42,
 *        then writes the encrypted values to "rotors.ini".
 * 
 * @param filename The name of the configuration file to read.
 */
void buildIni(char *filename) {
    // Open the configuration file for reading
    ifstream configFile(filename);
    if (!configFile.is_open()) {
        cerr << "Error: Unable to open configuration file " << filename << endl;
        exit(EXIT_FAILURE);
    }

    // Create or open "rotors.ini" for writing the encrypted values
    ofstream rotorsFile("rotors.ini");
    if (!rotorsFile.is_open()) {
        cerr << "Error: Unable to create or open rotors.ini" << endl;
        configFile.close();
        exit(EXIT_FAILURE);
    }

    int value;
    while (configFile >> value) {
        value ^= 42;  // XOR encryption with 42
        rotorsFile << value << "\n";
    }

    // Close both files after finishing
    configFile.close();
    rotorsFile.close();
}

/**
 * @brief Reads the "rotors.ini" file and initializes rotor1 and rotor2 arrays with the values read.
 * 
 * @param rotor1 Array to store rotor 1 configuration.
 * @param rotor2 Array to store rotor 2 configuration.
 */
void buildRotors(int rotor1[28], int rotor2[28]) {
    // Open "rotors.ini" file for reading
    ifstream rotorsFile("rotors.ini");
    if (!rotorsFile.is_open()) {
        cerr << "Error: Rotor machine not initialized. Run with -i option and provide an appropriate configuration file." << endl;
        exit(EXIT_FAILURE);
    }

    // Read the first 28 integers into rotor1
    for (int i = 0; i < 28; ++i) {
        rotorsFile >> rotor1[i];
    }

    // Read the next 28 integers into rotor2
    for (int i = 0; i < 28; ++i) {
        rotorsFile >> rotor2[i];
    }

    // Close the file after finishing
    rotorsFile.close();
}

/**
 * @brief Rotates a rotor array to the right by one position.
 * 
 * @param rotor The rotor array to rotate.
 */
void rotateRotorRight(int rotor[28]) {
    int temp = rotor[27];
    for (int i = 27; i > 0; --i) {
        rotor[i] = rotor[i - 1];
    }
    rotor[0] = temp;
}

/**
 * @brief Rotates a rotor array to the left by one position.
 * @param rotor The rotor array to rotate.
 */
void rotateRotorLeft(int rotor[28]) {
    int temp = rotor[0];
    for (int i = 0; i < 27; ++i) {
        rotor[i] = rotor[i + 1];
    }
    rotor[27] = temp;
}

/**
 * @brief Sets the initial position of rotor1 by rotating it to the right by the specified number of positions.
 * @param rotor The rotor array to set.
 * @param rotations The number of positions to rotate rotor1 to the right.
 */
void setRotor1(int rotor[28], int rotations) {
    for (int i = 0; i < rotations; ++i) {
        rotateRotorRight(rotor);
    }
}

/**
 * @brief Sets the initial position of rotor2 by rotating it to the left by the specified number of positions.
 * 
 * @param rotor The rotor array to set.
 * @param rotations The number of positions to rotate rotor2 to the left.
 */
void setRotor2(int rotor[28], int rotations) {
    for (int i = 0; i < rotations; ++i) {
        rotateRotorLeft(rotor);
    }
}

/**
 * @brief Converts a character to its corresponding index in the rotor configuration.
 * 
 * @param convert The character to convert.
 * @return The index corresponding to the character.
 */
int charToIndex(char convert) {
    if (convert == ' ') {
        return 26;
    } else if (convert == '.') {
        return 27;
    } else {
        return toupper(convert) - 'A';
    }
}

/**
 * @brief Converts an index to its corresponding character in the rotor configuration.
 * 
 * @param convert The index to convert.
 * @return The character corresponding to the index.
 */
char indexToChar(int convert) {
    if (convert == 26) {
        return ' ';
    } else if (convert == 27) {
        return '.';
    } else {
        return static_cast<char>(convert + 'A');
    }
}

/**
 * @brief Encrypts the contents of infile using the rotor machine and writes the encrypted
 *        output to outfile.
 * 
 * @param infile Input file stream to read from.
 * @param outfile Output file stream to write encrypted data to.
 * @param rotor1 Array representing rotor 1 configuration.
 * @param rotor2 Array representing rotor 2 configuration.
 */
void encryptFile(ifstream &infile, ofstream &outfile, int rotor1[28], int rotor2[28]) {
    char ch;
    while (infile.get(ch)) {
        if (ch == '\n') {
            outfile.put('\n');
            continue;
        }

        int index = charToIndex(ch);
        if (index < 0 || index >= 28) {
            cerr << "Error: Invalid character to index conversion: " << ch << " -> " << index << endl;
            continue;
        }

        int rotor1Value = rotor1[index];    // Get the value from rotor1
        int rotor2Index = -1;
        for (int i = 0; i < 28; ++i) {
            if (rotor2[i] == rotor1Value) {
                rotor2Index = i;
                break;
            }
        }
        if (rotor2Index == -1) {
            cerr << "Error: Invalid character in rotor2 mapping." << endl;
            exit(EXIT_FAILURE);
        }

        char encryptedChar = indexToChar(rotor2Index);
        outfile.put(encryptedChar);

        rotateRotorRight(rotor1);
        rotateRotorLeft(rotor2);
    }
}

/**
 * @brief Decrypts the contents of infile using the rotor machine and writes the decrypted
 *        output to outfile.
 * 
 * @param infile Input file stream to read from.
 * @param outfile Output file stream to write decrypted data to.
 * @param rotor1 Array representing rotor 1 configuration.
 * @param rotor2 Array representing rotor 2 configuration.
 */
void decryptFile(ifstream &infile, ofstream &outfile, int rotor1[28], int rotor2[28]) {
    char ch;
    while (infile.get(ch)) {
        if (ch == '\n') {
            outfile.put('\n');
            continue;
        }

        int index = charToIndex(ch);
        if (index < 0 || index >= 28) {
            cerr << "Error: Invalid character to index conversion: " << ch << " -> " << index << endl;
            continue;
        }

        int rotor2Value = rotor2[index];  // Get the value from rotor2
        int rotor1Index = -1;
        for (int i = 0; i < 28; ++i) {
            if (rotor1[i] == rotor2Value) {
                rotor1Index = i;
                break;
            }
        }
        if (rotor1Index == -1) {
            cerr << "Error: Invalid character in rotor1 mapping." << endl;
            exit(EXIT_FAILURE);
        }

        char decryptedChar = indexToChar(rotor1Index);
        outfile.put(decryptedChar);

        rotateRotorRight(rotor1);
        rotateRotorLeft(rotor2);
    }
}
