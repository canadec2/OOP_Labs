#include <algorithm>
#include "visitor.h"

void Visitor::doFightRound() {
    // Простой перебор всех пар NPC для боя
    for (size_t i = 0; i < npcs->size(); ++i) {
        for (size_t j = i+1; j < npcs->size(); ++j) {
            auto& npc1 = *(*npcs)[i];
            auto& npc2 = *(*npcs)[j];

            if (npc1.isDead() || npc2.isDead()) continue;

            double dist = distance(npc1, npc2);
            if (dist <= fightRange) {
                subject.notify("Начинается бой между " + npc1.getName() + " (" + npc1.getTypeName() + ") и " 
                               + npc2.getName() + " (" + npc2.getTypeName() + ")");

                // Простой бой: если один может атаковать другого — атакует.
                // Можно упростить: npc1 атакует npc2, потом npc2 атакует npc1
                if (npc1.canAttack(npc2)) npc1.attack(npc2);
                if (!npc2.isDead() && npc2.canAttack(npc1)) npc2.attack(npc1);

                // Результат боя
                if (npc1.isDead()) subject.notify("NPC " + npc1.getName() + " погиб.");
                if (npc2.isDead()) subject.notify("NPC " + npc2.getName() + " погиб.");
            }
        }
    }
    // Удалим мертвых
    npcs->erase(std::remove_if(npcs->begin(), npcs->end(), [](auto& ptr){return ptr->isDead();}), npcs->end());
}