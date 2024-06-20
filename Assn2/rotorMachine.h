/*
Author: Jun Song
Date: 06/19/2024
Description: Rotormachine with c++
*/

#ifndef ROTORMACHINE_H
#define ROTORMACHINE_H
#include <fstream>

using namespace std;

void buildIni(char *filename);
void buildRotors(int rotor1[28], int rotor2[28]);
void rotateRotorRight(int rotor[28]);
void rotateRotorLeft(int rotor[28]);
void setRotor1(int rotor[28], int rotations);
void setRotor2(int rotor[28], int rotations);
int charToIndex(char convert);
char indexToChar(int convert);
void encryptFile(ifstream &infile, ofstream &outfile, int rotor1[28], int rotor2[28]);
void decryptFile(ifstream &infile, ofstream &outfile, int rotor1[28], int rotor2[28]);

#endif
