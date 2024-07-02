/*
Name: Jun Song
Date: 07/01/2024
Description: Header file for the Zombie class, which represents a zombie with a type.
*/

#ifndef ZOMBIE_SONG_H
#define ZOMBIE_SONG_H

#include <iostream>

// Class declaration for Zombie
class Zombie {
private:
    char type;  // Type of zombie

public:
    // Constructors
    Zombie();        // Default constructor
    Zombie(char t);  // Parameterized constructor

    // Getter method for type
    char getType() const;

    // Overloaded equality operator
    bool operator==(const Zombie& other) const;

    // Overloaded stream insertion operator
    friend std::ostream& operator<<(std::ostream& os, const Zombie& zombie);
};

#endif // ZOMBIE_SONG_H

// Constructor definitions (if not inline)
Zombie::Zombie() : type('R') {}  // Default to 'R' for Red

Zombie::Zombie(char t) : type(t) {}

// Getter method
char Zombie::getType() const {
    return type;
}

// Overloaded equality operator
bool Zombie::operator==(const Zombie& other) const {
    return type == other.type;
}

// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& os, const Zombie& zombie) {
    os << zombie.type;
    return os;
}
