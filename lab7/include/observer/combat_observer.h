#pragma once
#include <string>
#include <memory>
#include "../npc/npc.h"

class CombatObserver {
public:
    virtual ~CombatObserver() = default;
    virtual void onCombat(const std::string& attacker, const std::string& defender, bool killed) = 0;
    virtual void onDeath(const std::string& npcName) = 0;
}; 