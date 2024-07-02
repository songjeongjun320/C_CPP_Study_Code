/*
Name : Jun Song
Date : 06/24/2024
Description : This program simulates terraforming by generating and modifying a 
landmass grid based on user inputs. Outputs include raw, normalized, and finalized 
landmass grids displayed on the console and saved to text files.
Usage : Compile and run the program. Optionally set a seed for random number generation.
terraformer [-s <seed>]
-s <seed>: Optional argument to set the random number generator seed.
Follow the prompts to enter grid width, height, waterline level, dirtball radius, power, and the number of dirtballs to drop
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <cstring>

using namespace std;

// Function declarations
void dropDirtBall(int** landmass, int maxWidth, int maxHeight, int centerX, int centerY, int radius, int power);
bool boundsCheck(int x, int y, int minx, int miny, int maxx, int maxy);
int findMax(int** map, int width, int height);
void normalizeMap(int** map, int width, int height, int maxVal);
void printLand(int** land, int width, int height, ostream& out);
char** finalizeMap(int** map, int width, int height, int waterline);
double frand();

// Main function
int main(int argc, char** argv) {
    int width, height, waterline, radius, power, numDirtballs;
    unsigned int seed = static_cast<unsigned int>(time(0)); // Default seed

    // Parse command line arguments for seed
    if (argc >= 2 && strcmp(argv[1], "-s") == 0) {
        cout << "seed before casting : " << argv[2] << endl;
        seed = static_cast<int>(atoi(argv[2]));
        cout << "Using seed: " << seed << endl;
    } else {
        cout << "Using default seed: " << seed << endl;
    }
    srand(seed);

    // User input prompts
    cout << "Welcome to the CSE240 Terraformer!!" << endl;
    cout << "Enter grid width: ";
    cin >> width;
    cout << "Enter grid height: ";
    cin >> height;
    cout << "Enter value for waterline (40-200): ";
    cin >> waterline;
    cout << "Enter dirtball radius (minimum 2): ";
    cin >> radius;
    cout << "Enter dirtball power rating (minimum = radius): ";
    cin >> power;
    cout << "Enter number of dirtballs to drop: ";
    cin >> numDirtballs;

    // Create and initialize landmass array
    int** landmass = new int*[height];
    for (int i = 0; i < height; i++) {
        landmass[i] = new int[width]();
    }

    // Drop dirtballs
    for (int i = 0; i < numDirtballs; i++) {
        int centerX = (int)(frand() * width);
        int centerY = (int)(frand() * height);
        dropDirtBall(landmass, width, height, centerX, centerY, radius, power);
    }

    // Print raw landmass to console and file
    ofstream rawFile("raw_landmass.txt");
    printLand(landmass, width, height, cout);
    printLand(landmass, width, height, rawFile);
    rawFile.close();

    // Normalize the landmass
    int maxVal = findMax(landmass, width, height);
    normalizeMap(landmass, width, height, maxVal);

    // Print normalized landmass to console and file
    ofstream normFile("normalized_landmass.txt");
    printLand(landmass, width, height, cout);
    printLand(landmass, width, height, normFile);
    normFile.close();

    // Finalize the map
    char** finalMap = finalizeMap(landmass, width, height, waterline);

    // Print polished landmass to console and file
    ofstream finalFile("final_landmass.txt");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout << finalMap[i][j];
            finalFile << finalMap[i][j];
        }
        cout << endl;
        finalFile << endl;
    }
    finalFile.close();

    // Clean up
    for (int i = 0; i < height; i++) {
        delete[] landmass[i];
        delete[] finalMap[i];
    }
    delete[] landmass;
    delete[] finalMap;

    return 0;
}

// Function to drop a dirtball on the landmass
void dropDirtBall(int** landmass, int maxWidth, int maxHeight, int centerX, int centerY, int radius, int power) {
    for (int y = centerY - radius; y <= centerY + radius; y++) {
        for (int x = centerX - radius; x <= centerX + radius; x++) {
            if (boundsCheck(x, y, 0, 0, maxWidth, maxHeight)) {
                double distance = sqrt(pow(x - centerX, 2) + pow(y - centerY, 2));
                if (distance <= radius) {
                    int impactValue = power - static_cast<int>(floor(distance));
                    landmass[y][x] += impactValue;
                }
            }
        }
    }
}

// Function to check if the coordinates are within the bounds
bool boundsCheck(int x, int y, int minx, int miny, int maxx, int maxy) {
    return x >= minx && x < maxx && y >= miny && y < maxy;
}

// Function to generate a random floating-point number between 0 and 1
double frand() {
    return (double)rand() / ((double)RAND_MAX + 1);
}

// Function to find the maximum value in the landmass array
int findMax(int** map, int width, int height) {
    int maxVal = map[0][0];
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map[y][x] > maxVal) {
                maxVal = map[y][x];
            }
        }
    }
    return maxVal;
}

// Function to normalize the values in the landmass array to a range of 0-255
void normalizeMap(int** map, int width, int height, int maxVal) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            map[y][x] = static_cast<int>((static_cast<double>(map[y][x]) / maxVal) * 255);
        }
    }
}

// Function to print the landmass array
void printLand(int** land, int width, int height, ostream& out) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            out << setw(4) << land[y][x];
        }
        out << endl;
    }
}

// Function to create a finalized map with water and land represented by different characters
char** finalizeMap(int** map, int width, int height, int waterline) {
    char** charMap = new char*[height];
    for (int i = 0; i < height; i++) {
        charMap[i] = new char[width];
    }

    int landzone = 255 - waterline;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int value = map[y][x];
            if (value < floor(0.5 * static_cast<double>(waterline))) {
                charMap[y][x] = '#'; // Deep water
            } else if (value >= floor(0.5 * static_cast<double>(waterline)) && value <= waterline) {
                charMap[y][x] = '~'; // Shallow water
            } else if (value > waterline) {
                double landzoneFactor = static_cast<double>(landzone);
                if (value < (waterline + floor(0.15 * landzoneFactor))) {
                    charMap[y][x] = '.'; // Low land
                } else if (value >= (waterline + floor(0.15 * landzoneFactor)) && value < (waterline + floor(0.4 * landzoneFactor))) {
                    charMap[y][x] = '-'; // Medium land
                } else if (value >= (waterline + floor(0.4 * landzoneFactor)) && value < (waterline + floor(0.8 * landzoneFactor))) {
                    charMap[y][x] = '*'; // High land
                } else {
                    charMap[y][x] = '^'; // Mountain
                }
            }
        }
    }

    return charMap;
}
