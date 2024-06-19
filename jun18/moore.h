/*
moore.h contains forward declarations for a moore neightborhood test program
You can create a 2d array, initialize it and drop moore neighborhoods into it
*/

#pragma once
#ifndef MOORE_H
#define MOORE_H

int** makeTwoDArray(int, int);
void initTwoDArray(int**, int, int, int);
void printArray(int**, int, int);
void mooreDrop(int**, int, int, int, int);
bool boundsCheck(int px, int py, int minx, int miny, int maxx, int maxy);

#endif