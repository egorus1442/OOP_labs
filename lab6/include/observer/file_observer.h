#pragma once
#include "combat_observer.h"
#include <fstream>

class FileObserver : public CombatObserver {
public:
    FileObserver(const std::string& filename);
    void onCombat(const std::string& attacker, const std::string& defender, bool killed) override;
    void onDeath(const std::string& npcName) override;
private:
    std::ofstream file_;
}; 