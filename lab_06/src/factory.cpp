#include "factory.h"
#include "bear.h"
#include "vup.h"
#include "vykhukhol.h"
#include <iostream>

std::unique_ptr<NPC> Factory::createNPC(const std::string& type, double x, double y, const std::string& name) {
    if (type == "Bear") return std::make_unique<Bear>(x, y, name);
    if (type == "Vup") return std::make_unique<Vup>(x, y, name);
    if (type == "Vykhukhol") return std::make_unique<Vykhukhol>(x, y, name);
    return nullptr;
}

void Factory::saveToFile(const std::string& filename, const std::vector<std::unique_ptr<NPC>>& npcs) {
    std::ofstream out(filename);
    for (auto& npc : npcs) {
        out << npc->getTypeName() << " " << npc->getX() << " " << npc->getY() << " " << npc->getName() << "\n";
    }
}

std::vector<std::unique_ptr<NPC>> Factory::loadFromFile(const std::string& filename) {
    std::vector<std::unique_ptr<NPC>> res;
    std::ifstream in(filename);
    if (!in) return res;

    std::string type, name;
    double x,y;
    while (in >> type >> x >> y >> name) {
        auto npc = createNPC(type, x, y, name);
        if (npc) res.push_back(std::move(npc));
    }
    return res;
}