#include "gtest/gtest.h"
#include "../src/npc.h"
#include "../src/bear.h"
#include "../src/vup.h"
#include "../src/vykhukhol.h"
#include "../src/factory.h"
#include "../src/visitor.h"
#include "../src/observers.h"
#include <memory>
#include <fstream>

// Мок-объект для Observer
class MockObserver : public Observer {
public:
    std::string lastEvent;
    void onEvent(const std::string& msg) override {
        lastEvent = msg;
    }
};

// Тест: проверяем, что объекты создаются
TEST(FactoryTest, CreateBear) {
    auto bear = Factory::createNPC("Bear", 100, 200, "BearOne");
    ASSERT_NE(bear, nullptr);
    ASSERT_EQ(bear->getTypeName(), "Bear");
    ASSERT_EQ(bear->getX(), 100);
    ASSERT_EQ(bear->getY(), 200);
    ASSERT_EQ(bear->getName(), "BearOne");
}

TEST(FactoryTest, CreateVup) {
    auto vup = Factory::createNPC("Vup", 300, 400, "VupOne");
    ASSERT_NE(vup, nullptr);
    ASSERT_EQ(vup->getTypeName(), "Vup");
    ASSERT_EQ(vup->getX(), 300);
    ASSERT_EQ(vup->getY(), 400);
    ASSERT_EQ(vup->getName(), "VupOne");
}

TEST(FactoryTest, CreateVykhukhol) {
    auto vyk = Factory::createNPC("Vykhukhol", 500, 600, "VykOne");
    ASSERT_NE(vyk, nullptr);
    ASSERT_EQ(vyk->getTypeName(), "Vykhukhol");
    ASSERT_EQ(vyk->getX(), 500);
    ASSERT_EQ(vyk->getY(), 600);
    ASSERT_EQ(vyk->getName(), "VykOne");
}

// Тест сохранения/загрузки
TEST(FactoryTest, SaveLoad) {
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(Factory::createNPC("Bear", 10, 10, "BearOne"));
    npcs.push_back(Factory::createNPC("Vup", 20, 20, "VupOne"));
    npcs.push_back(Factory::createNPC("Vykhukhol", 30, 30, "VykOne"));

    Factory::saveToFile("test_npcs.txt", npcs);
    auto loaded = Factory::loadFromFile("test_npcs.txt");
    ASSERT_EQ(loaded.size(), 3);
    ASSERT_EQ(loaded[0]->getTypeName(), "Bear");
    ASSERT_EQ(loaded[0]->getName(), "BearOne");
    ASSERT_EQ(loaded[1]->getTypeName(), "Vup");
    ASSERT_EQ(loaded[2]->getTypeName(), "Vykhukhol");
}

// Тест логики боя
// Медведь ест всех кроме медведей
TEST(FightTest, BearEatsVup) {
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(Factory::createNPC("Bear", 0, 0, "BearA"));
    npcs.push_back(Factory::createNPC("Vup", 0, 1, "VupA"));

    Subject subject;
    MockObserver mockObs;
    subject.addObserver(&mockObs);

    Visitor visitor(5.0, subject, &npcs);
    visitor.doFightRound();

    // После боя Vup должен быть убит, список уменьшится до 1
    ASSERT_EQ(npcs.size(), 1);
    ASSERT_EQ(npcs[0]->getTypeName(), "Bear");
    ASSERT_TRUE(mockObs.lastEvent.find("VupA") != std::string::npos);
}

// Выхухоль убивает медведей
TEST(FightTest, VykhukholKillsBear) {
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(Factory::createNPC("Bear", 0, 0, "BearB"));
    npcs.push_back(Factory::createNPC("Vup", 1, 1, "VupB"));
    npcs.push_back(Factory::createNPC("Vykhukhol", 2, 2, "VykB"));

    Subject subject;
    MockObserver mockObs;
    subject.addObserver(&mockObs);

    Visitor visitor(5.0, subject, &npcs);
    visitor.doFightRound();

    // Выхухоль убьет медведя
    ASSERT_EQ(npcs.size(), 1);
    ASSERT_EQ(npcs[0]->getTypeName(), "Vykhukhol");
    ASSERT_TRUE(mockObs.lastEvent.find("BearB погиб") != std::string::npos);
}

// Vup никого не атакует, если рядом Bear и Vup - медведь атакует Vup
TEST(FightTest, VupDoesNotHarmAnyone) {
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(Factory::createNPC("Vup", 0, 0, "VupC"));
    npcs.push_back(Factory::createNPC("Bear", 1, 1, "BearC"));

    Subject subject;
    MockObserver mockObs;
    subject.addObserver(&mockObs);

    Visitor visitor(5.0, subject, &npcs);
    visitor.doFightRound();

    // Медведь убивает Vup, остается 1 - медведь
    ASSERT_EQ(npcs.size(), 1);
    ASSERT_EQ(npcs[0]->getTypeName(), "Bear");
}

// Проверка Observer: при добавлении или смерти есть уведомление
TEST(ObserverTest, NotifyOnEvents) {
    std::vector<std::unique_ptr<NPC>> npcs;
    Subject subject;
    MockObserver mockObs;
    subject.addObserver(&mockObs);

    // Добавляем NPC
    npcs.push_back(Factory::createNPC("Bear", 0, 0, "BearX"));
    subject.notify("Добавлен BearX");
    ASSERT_EQ(mockObs.lastEvent, "Добавлен BearX");
}

// Запуск всех тестов
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}