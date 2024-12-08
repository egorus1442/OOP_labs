#pragma once
#include "npc.h"

class Bear : public NPC {
public:
    void accept(CombatVisitor& visitor) override;
    std::string getType() const override { return "Bear"; }
    double getMoveSpeed() const override { return 5.0; }
    double getCombatDistance() const override { return 10.0; }
}; 