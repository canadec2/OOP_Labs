#include "../include/solution.hpp"
#include <iostream>
#include <memory>
#include <vector>

int main() {
    std::vector<Point<int>> hexPoints{{0, 0}, {2, 0}, {3, 2}, {2, 4}, {0, 4}, {-1, 2}};
    auto hexagon = std::make_shared<Hexagon<int>>(hexPoints);

    hexagon->print(std::cout);
    std::cout << "\nArea: " << hexagon->area() << std::endl;

    auto center = hexagon->geometricCenter();
    std::cout << "Geometric center: (" << center.x << ", " << center.y << ")" << std::endl;

    return 0;
}
