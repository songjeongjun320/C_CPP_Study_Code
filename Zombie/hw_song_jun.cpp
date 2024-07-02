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
        char randomType = types[std::rand() % 6];
        Zombie z(randomType);

        int action = std::rand() % 2;
        if (action == 0) {
            congaLine.AddToFront(z);
            std::cout << "Added to front: " << z << std::endl;
        } else {
            congaLine.AddToEnd(z);
            std::cout << "Added to end: " << z << std::endl;
        }
    }

    congaLine.PrintList();

    return 0;
}
