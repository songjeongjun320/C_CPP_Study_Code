#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

// Function declarations
void dropDirtBall(int** landmass, int maxWidth, int maxHeight, int centerX, int centerY, int radius, int power);
bool boundsCheck(int x, int y, int minx, int miny, int maxx, int maxy);
int findMax(int** map, int width, int height);
void normalizeMap(int** map, int width, int height, int maxVal);
void printLand(int** land, int width, int height, ostream& out);
char** finalizeMap(int** map, int width, int height, int waterline);

// Main function
int main(int argc, char** argv) {
    int width, height, waterline, radius, power, numDirtballs;
    unsigned int seed = time(0);

    // Parse command line arguments for seed
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "-s" && i + 1 < argc) {
            seed = atoi(argv[++i]);
        }
    }

    srand(seed);

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
        int centerX = rand() % width;
        int centerY = rand() % height;
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

// Function definitions
void dropDirtBall(int** landmass, int maxWidth, int maxHeight, int centerX, int centerY, int radius, int power) {
    for (int y = centerY - radius; y <= centerY + radius; y++) {
        for (int x = centerX - radius; x <= centerX + radius; x++) {
            if (boundsCheck(x, y, 0, 0, maxWidth, maxHeight)) {
                double distance = sqrt(pow(x - centerX, 2) + pow(y - centerY, 2));
                if (distance <= radius) {
                    int impactValue = power - static_cast<int>(distance);
                    landmass[y][x] += impactValue;
                }
            }
        }
    }
}

bool boundsCheck(int x, int y, int minx, int miny, int maxx, int maxy) {
    return x >= minx && x < maxx && y >= miny && y < maxy;
}

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

void normalizeMap(int** map, int width, int height, int maxVal) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            map[y][x] = static_cast<int>((static_cast<double>(map[y][x]) / maxVal) * 255);
        }
    }
}

void printLand(int** land, int width, int height, ostream& out) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            out << setw(4) << land[y][x];
        }
        out << endl;
    }
}

char** finalizeMap(int** map, int width, int height, int waterline) {
    char** charMap = new char*[height];
    for (int i = 0; i < height; i++) {
        charMap[i] = new char[width];
    }

    int landzone = 255 - waterline;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int value = map[y][x];
            if (value < 0.5 * waterline) {
                charMap[y][x] = '#';
            } else if (value >= 0.5 * waterline && value <= waterline) {
                charMap[y][x] = '~';
            } else if (value > waterline && value < (waterline + 0.15 * landzone)) {
                charMap[y][x] = '.';
            } else if (value >= (waterline + 0.15 * landzone) && value < (waterline + 0.4 * landzone)) {
                charMap[y][x] = '-';
            } else if (value >= (waterline + 0.4 * landzone) && value < (waterline + 0.8 * landzone)) {
                charMap[y][x] = '*';
            } else {
                charMap[y][x] = '^';
            }
        }
    }

    return charMap;
}
