/*
Author: Jun Song
Date: 06/19/2024
Description: Rotormachine with c++
*/
#ifndef ROTORMACHINE_H
#define ROTORMACHINE_H

#include <fstream> // Include necessary header for file operations

using namespace std;

// Function prototypes for the rotor machine operations

/**
 * @brief Reads a configuration file and generates an initialization file for rotors.
 * 
 * @param filename The name of the configuration file.
 */
void buildIni(char *filename);

/**
 * @brief Builds the rotor configurations from a previously generated initialization file.
 * 
 * @param rotor1 Array to store the first rotor configuration.
 * @param rotor2 Array to store the second rotor configuration.
 */
void buildRotors(int rotor1[28], int rotor2[28]);

/**
 * @brief Rotates a rotor to the right.
 * 
 * @param rotor Array representing the rotor to rotate.
 */
void rotateRotorRight(int rotor[28]);

/**
 * @brief Rotates a rotor to the left.
 * 
 * @param rotor Array representing the rotor to rotate.
 */
void rotateRotorLeft(int rotor[28]);

/**
 * @brief Sets the initial position of rotor 1.
 * 
 * @param rotor Array representing rotor 1.
 * @param rotations Number of positions to rotate rotor 1 initially.
 */
void setRotor1(int rotor[28], int rotations);

/**
 * @brief Sets the initial position of rotor 2.
 * 
 * @param rotor Array representing rotor 2.
 * @param rotations Number of positions to rotate rotor 2 initially.
 */
void setRotor2(int rotor[28], int rotations);

/**
 * @brief Converts a character to its corresponding index (0-27) for encryption/decryption.
 * 
 * @param convert Character to convert.
 * @return Corresponding index in the range [0, 27].
 */
int charToIndex(char convert);

/**
 * @brief Converts an index (0-27) back to its corresponding character.
 * 
 * @param convert Index to convert.
 * @return Corresponding character.
 */
char indexToChar(int convert);

/**
 * @brief Encrypts data from an input file using the rotor machine.
 * 
 * @param infile Input file stream to read data from.
 * @param outfile Output file stream to write encrypted data to.
 * @param rotor1 Array representing rotor 1 configuration.
 * @param rotor2 Array representing rotor 2 configuration.
 */
void encryptFile(ifstream &infile, ofstream &outfile, int rotor1[28], int rotor2[28]);

/**
 * @brief Decrypts data from an input file using the rotor machine.
 * 
 * @param infile Input file stream to read encrypted data from.
 * @param outfile Output file stream to write decrypted data to.
 * @param rotor1 Array representing rotor 1 configuration.
 * @param rotor2 Array representing rotor 2 configuration.
 */
void decryptFile(ifstream &infile, ofstream &outfile, int rotor1[28], int rotor2[28]);

#endif
