#pragma once
#include "npc.h"

class Knight : public NPC {
public:
    void accept(CombatVisitor& visitor) override;
    std::string getType() const override { return "Knight"; }
    double getMoveSpeed() const override { return 30.0; }
    double getCombatDistance() const override { return 10.0; }
}; 