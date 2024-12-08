#pragma once
#include "npc.h"

class Orc : public NPC {
public:
    void accept(CombatVisitor& visitor) override;
    std::string getType() const override { return "Orc"; }
}; 