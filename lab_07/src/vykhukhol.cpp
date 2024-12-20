#include "vykhukhol.h"
#include "bear.h"
#include "vup.h"
#include "common.h"
#include <iostream>

Vykhuhol::Vykhuhol(int x, int y) : NPC(VykhuholType, x, y) {}
Vykhuhol::Vykhuhol(std::istream &is) : NPC(VykhuholType, is) {}

void Vykhuhol::print() {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Vykhuhol at (" << x << ", " << y << ")\n";
}

bool Vykhuhol::accept(Visitor &visitor) {
    return visitor.visit(*this);
}

void Vykhuhol::save(std::ostream &os) {
    std::lock_guard<std::mutex> lock(mtx);
    os << VykhuholType << " " << x << " " << y << std::endl;
}

void Vykhuhol::move() {
    int dx = randOffset(5);
    int dy = randOffset(5);
    {
        std::lock_guard<std::mutex> lock(mtx);
        x += dx;
        y += dy;
        if (x < 0) x=0; if (y < 0) y=0; if (x>100) x=100; if (y>100) y=100; 
    }
}

std::ostream &operator<<(std::ostream &os, Vykhuhol &vykhuhol) {
    os << "Vykhuhol: (" << vykhuhol.x << ", " << vykhuhol.y << ")";
    return os;
}