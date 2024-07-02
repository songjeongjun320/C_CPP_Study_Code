/*
Name: Jun Song
Date: 07/01/2024
Description: This program simulates a zombie conga line using a templated doubly-linked list.
Usage: 
    Compile the program using the provided Makefile:
        make
    Run the executable:
        ./exe
    This will generate a conga line of zombies with random types, adding them either to the front or the end of the list.
*/

#include "linkedlist_song.hpp"
#include "zombie_song.h"
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(std::time(nullptr));

    LinkedList<Zombie> congaLine;

    // Simulate actions with Zombies
    for (int i = 0; i < 10; i++) {
        char types[] = {'R', 'Y', 'G', 'B', 'M', 'C'};
        char randomType = types[std::rand() % 6]; // Randomly select a zombie type
        Zombie z(randomType);

        int action = std::rand() % 2; // Randomly decide whether to add to the front or the end
        if (action == 0) {
            congaLine.AddToFront(z);
            std::cout << "Added to front: " << z << std::endl;
        } else {
            congaLine.AddToEnd(z);
            std::cout << "Added to end: " << z << std::endl;
        }
    }

    // Print the final conga line of zombies
    congaLine.PrintList();

    return 0;
}