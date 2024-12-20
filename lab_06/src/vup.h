#pragma once
#include "npc.h"

class Vup : public NPC {
    bool dead;
public:
    Vup(double x_, double y_, const std::string& name_) : NPC(x_, y_, name_), dead(false) {}
    std::string getTypeName() const override { return "Vup"; }
    void accept(Visitor& visitor) override;

    bool canAttack(const NPC&) const override {
        return false; 
    }
    bool isDead() const override { return dead; }
    void setDead(bool d) override { dead = d; }
    void attack(NPC&) override {
        // Вы́п не атакует
    }
};