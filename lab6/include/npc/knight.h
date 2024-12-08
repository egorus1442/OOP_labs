#pragma once
#include "npc.h"

class Knight : public NPC {
public:
    void accept(CombatVisitor& visitor) override;
    std::string getType() const override { return "Knight"; }
}; 