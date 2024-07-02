#ifndef ZOMBIE_<LASTNAME>_H
#define ZOMBIE_<LASTNAME>_H

#include <iostream>

class Zombie {
private:
    char type;

public:
    Zombie() : type('R') {}  // Default to 'R' for Red
    Zombie(char t) : type(t) {}

    char getType() const {
        return type;
    }

    bool operator==(const Zombie& other) const {
        return type == other.type;
    }

    friend std::ostream& operator<<(std::ostream& os, const Zombie& zombie) {
        os << zombie.type;
        return os;
    }
};

#endif // ZOMBIE_<LASTNAME>_H
