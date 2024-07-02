#include "zombie_song.h"
#include <iostream>

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

// Add any additional methods if necessary
// For example, you might want methods to change the type of a zombie, etc.

