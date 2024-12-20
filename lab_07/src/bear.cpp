#include "bear.h"
#include "vup.h"
#include "vykhukhol.h"
#include "common.h"
#include <iostream>

Bear::Bear(int x, int y) : NPC(BearType, x, y) {}
Bear::Bear(std::istream &is) : NPC(BearType, is) {}

void Bear::print() { 
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Bear at (" << x << ", " << y << ")\n";
}

bool Bear::accept(Visitor &visitor) { return visitor.visit(*this); }

void Bear::save(std::ostream &os) {
    std::lock_guard<std::mutex> lock(mtx);
    os << BearType << " " << x << " " << y << std::endl;
}

void Bear::move() {
    int dx = randOffset(5);
    int dy = randOffset(5);
    {
        std::lock_guard<std::mutex> lock(mtx);
        x += dx;
        y += dy;
        if (x < 0) x=0; if (y < 0) y=0; if (x>100) x=100; if (y>100) y=100; 
    }
}

std::ostream &operator<<(std::ostream &os, Bear &bear) {
    os << "Bear: (" << bear.x << ", " << bear.y << ")";
    return os;
}