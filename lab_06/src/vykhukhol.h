#pragma once
#include "npc.h"

class Vykhukhol : public NPC {
    bool dead;
public:
    Vykhukhol(double x_, double y_, const std::string& name_) : NPC(x_, y_, name_), dead(false) {}
    std::string getTypeName() const override { return "Vykhukhol"; }
    void accept(Visitor& visitor) override;

    bool canAttack(const NPC& other) const override {
        return other.getTypeName() == "Bear";
    }
    bool isDead() const override { return dead; }
    void setDead(bool d) override { dead = d; }

    void attack(NPC& other) override {
        // Выхухоль убивает медведей
        if (other.getTypeName() == "Bear") {
            other.setDead(true);
        }
    }
};