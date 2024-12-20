#pragma once
#include <vector>
#include <cmath>
#include "bear.h"
#include "vup.h"
#include "vykhukhol.h"
#include "observers.h"

class Visitor {
    double fightRange;
    Subject& subject; // для уведомления
    std::vector<std::unique_ptr<NPC>>* npcs;
public:
    Visitor(double range, Subject& subj, std::vector<std::unique_ptr<NPC>>* npcs_) 
        : fightRange(range), subject(subj), npcs(npcs_) {}

    void visit(Bear& bear) {}
    void visit(Vup& vup) {}
    void visit(Vykhukhol& vyk) {}

    void doFightRound();

private:
    double distance(const NPC& a, const NPC& b) {
        double dx = a.getX() - b.getX();
        double dy = a.getY() - b.getY();
        return std::sqrt(dx*dx + dy*dy);
    }
};