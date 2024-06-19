/*
    let's write some code
    we're going to prompt the user for rows and columns
    make a dynamic 2d array
    fill it with zeroes

    then we're going to drop random moore neighborhoods into the array
*/

#include "moore.h"
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <stdlib.h>
using namespace std;

int main(int argv, char** argc){
    int rows;
    int cols;
    int drops;
    int** landArray;

    cout << "Enter number of rows : ";
    cin >> rows;
    cout << "Enter number of columns : ";
    cin >> cols;
    cout << "Enter number of drops : ";
    cin >> drops;

    landArray = makeTwoDArray(rows, cols);
    initTwoDArray(landArray, rows, cols,0);
    printArray(landArray,rows, cols);

    for(int drop = 0; drop < drops; drop++){
        int cy = rand() % rows;
        int cx = rand() % cols;

        mooreDrop(landArray, rows, cols, cy, cx);
        cout << "\n\n\nFINAL LAND : " << endl;
        printArray(landArray,rows, cols);
    }

    for(int y = 0; y < rows; y++){
        delete[] landArray[y];
    }
    delete[] landArray; 
}

int** makeTwoDArray(int rows, int cols){
    int** array = new int*[rows];
    for(int y = 0; y < rows; y++){
        array[y] = new int[cols];
    }
    return array;
}

void initTwoDArray(int** array, int rows, int cols, int iValue){
    for(int y = 0; y < rows; y++){
        for(int x = 0; x < cols; x++){
            array[y][x] = iValue;
        }
    }
}

void printArray(int**array, int rows, int cols){
    cout << "=============================================\n";
    for(int y = 0; y < rows; y++){
        for(int x = 0; x < cols; x++){
            cout << setw(3) << array[y][x];
        }
        cout << endl;
    }
    cout << "=============================================\n";
}

bool boundsCheck(int py, int px, int miny, int minx, int maxy, int maxx){
    if((px < minx) || (px > maxx)){return false;}
    if((py < miny) || (py > maxy)){return false;}
    return true;
}


void mooreDrop(int** array, int rows, int cols, int centerY, int centerX){
    /*
        ###
        #*#
        ###
    */

   for(int y = -1; y <= 1; y++){
    for(int x = -1; x <= 1; x++){
        if(boundsCheck(centerY + y, centerX + x,0,0,rows - 1 , cols - 1)){
            array[centerY + y][centerX + x] += 1;
        }
    }
   }
}