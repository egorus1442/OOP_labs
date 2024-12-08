#pragma once
#include "combat_observer.h"

class ConsoleObserver : public CombatObserver {
public:
    void onCombat(const std::string& attacker, const std::string& defender, bool killed) override;
    void onDeath(const std::string& npcName) override;
}; 