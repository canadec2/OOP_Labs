#include "vup.h"
#include "bear.h"
#include "vykhukhol.h"
#include "common.h"
#include <iostream>

Vup::Vup(int x, int y) : NPC(VupType, x, y) {}
Vup::Vup(std::istream &is) : NPC(VupType, is) {}

void Vup::print() {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Vup at (" << x << ", " << y << ")\n";
}

bool Vup::accept(Visitor &visitor) { 
    return visitor.visit(*this);
}

void Vup::save(std::ostream &os) {
    std::lock_guard<std::mutex> lock(mtx);
    os << VupType << " " << x << " " << y << std::endl;
}

void Vup::move() {
    int dx = randOffset(50);
    int dy = randOffset(50);
    {
        std::lock_guard<std::mutex> lock(mtx);
        x += dx;
        y += dy;
        if (x < 0) x=0; if (y < 0) y=0; if (x>100) x=100; if (y>100) y=100; 
    }
}

std::ostream &operator<<(std::ostream &os, Vup &vup) {
    os << "Vup: (" << vup.x << ", " << vup.y << ")";
    return os;
}