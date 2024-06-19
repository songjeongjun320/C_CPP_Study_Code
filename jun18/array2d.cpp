#include <iostream>
#include <stdio.h>
using std::cout;
using std::endl;
using std::cin;

int main(int argc, char** argv){
    int numRows;
    int numCols;

    int** array;
    int* rowsizes;

    cout << "Enter number of rows: ";
    cin >> numRows;
    cout << "Enter number of columns: ";
    cin >> numCols;

    array = new int*[numRows];
    rowsizes = new int[numRows];
    for(int y = 0; y < numRows; y++){
        rowsizes[y] = rand()%numCols + 1;
        array[y] = new int[rowsizes[y]];
    }

    for(int y = 0; y < numRows; y++){
        for(int x = 0; x < numCols; x++){
            array[y][x] = y + x;
        }
    }

    for(int y = 0; y < numRows; y++){
        for(int x = 0; x < rowsizes[y]; x++){
            cout << array[y][x] << " ";
        }
        cout << endl;
    }

    for(int y = 0; y < numRows; y++){
        delete[] array[y];
    }
    delete[] array;
}