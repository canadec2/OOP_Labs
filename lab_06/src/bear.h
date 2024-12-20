#pragma once
#include "npc.h"

class Bear : public NPC {
    bool dead;
public:
    Bear(double x_, double y_, const std::string& name_) : NPC(x_, y_, name_), dead(false) {}
    std::string getTypeName() const override { return "Bear"; }
    void accept(Visitor& visitor) override;

    bool canAttack(const NPC& other) const override {
        return other.getTypeName() != "Bear";
    }

    bool isDead() const override { return dead; }
    void setDead(bool d) override { dead = d; }

    void attack(NPC& other) override {
        // Медведь убивает всех, кроме медведей
        if (canAttack(other)) {
            other.setDead(true);
        }
    }
};