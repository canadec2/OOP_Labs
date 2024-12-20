#include <iostream>
#include <memory>
#include "factory.h"
#include "observers.h"
#include "visitor.h"

int main() {
    Subject subject;
    ConsoleObserver consoleObs;
    FileObserver fileObs("log.txt");
    subject.addObserver(&consoleObs);
    subject.addObserver(&fileObs);

    // Создаём NPC
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(Factory::createNPC("Bear", 10, 10, "BearOne"));
    npcs.push_back(Factory::createNPC("Vup", 12, 12, "VupOne"));
    npcs.push_back(Factory::createNPC("Vykhukhol", 11, 11, "VykOne"));

    for (auto& n : npcs) {
        subject.notify("Добавлен NPC: " + n->getName() + " типа " + n->getTypeName() 
                       + " на координаты (" + std::to_string(n->getX()) + ", " 
                       + std::to_string(n->getY()) + ")");
    }

    // Сохраняем в файл
    Factory::saveToFile("npcs.txt", npcs);

    // Загружаем из файла для проверки
    auto loadedNPC = Factory::loadFromFile("npcs.txt");
    subject.notify("Загружено NPC из файла: " + std::to_string(loadedNPC.size()));

    // Печатаем
    std::cout << "NPC в памяти:" << std::endl;
    for (auto& n : loadedNPC) {
        std::cout << n->getName() << " (" << n->getTypeName() << ")"
                  << " @(" << n->getX() << "," << n->getY() << ")\n";
    }

    // Запускаем бой
    Visitor visitor(5.0, subject, &loadedNPC);
    visitor.doFightRound();

    // Итоговый список после боя
    std::cout << "\nПосле боя осталось:\n";
    for (auto& n : loadedNPC) {
        std::cout << n->getName() << " (" << n->getTypeName() << ")"
                  << " @(" << n->getX() << "," << n->getY() << ")\n";
    }

    // Сохраняем итог
    Factory::saveToFile("npcs_after_fight.txt", loadedNPC);

    return 0;
}