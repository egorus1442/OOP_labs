#pragma once
#include "npc.h"

class Bear : public NPC {
public:
    void accept(CombatVisitor& visitor) override;
    std::string getType() const override { return "Bear"; }
}; 