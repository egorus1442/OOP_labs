#pragma once
#include <memory>
#include <vector>
#include <string>
#include "../observer/combat_observer.h"

// Forward declarations
class Orc;
class Knight;
class Bear;
class NPC;

class CombatVisitor {
public:
    void addObserver(std::shared_ptr<CombatObserver> observer);
    void removeObserver(std::shared_ptr<CombatObserver> observer);
    void notifyObservers(const std::string& attacker, const std::string& defender, bool killed);
    void notifyDeath(const std::string& npcName);
    
    void visit(Orc& orc);
    void visit(Knight& knight);
    void visit(Bear& bear);
    
    void setOpponent(std::shared_ptr<NPC> opponent);
    bool wasKilled() const;

protected:
    std::vector<std::shared_ptr<CombatObserver>> observers_;
    std::shared_ptr<NPC> opponent_;
    bool killed_ = false;
};