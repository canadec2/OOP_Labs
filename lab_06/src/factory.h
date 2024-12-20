#pragma once
#include <string>
#include <memory>
#include <fstream>
#include <vector>
#include "npc.h"

class Factory {
public:
    static std::unique_ptr<NPC> createNPC(const std::string& type, double x, double y, const std::string& name);

    static void saveToFile(const std::string& filename, const std::vector<std::unique_ptr<NPC>>& npcs);
    static std::vector<std::unique_ptr<NPC>> loadFromFile(const std::string& filename);
};