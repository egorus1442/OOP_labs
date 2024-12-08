#pragma once
#include "npc.h"

class Orc : public NPC {
public:
    void accept(CombatVisitor& visitor) override;
    std::string getType() const override { return "Orc"; }
    double getMoveSpeed() const override { return 20.0; }
    double getCombatDistance() const override { return 10.0; }
}; 