#include "../../include/visitor/combat_visitor.h"
#include "../../include/npc/orc.h"
#include "../../include/npc/knight.h"
#include "../../include/npc/bear.h"
#include <algorithm>

void CombatVisitor::addObserver(std::shared_ptr<CombatObserver> observer) {
    observers_.push_back(observer);
}

void CombatVisitor::removeObserver(std::shared_ptr<CombatObserver> observer) {
    observers_.erase(
        std::remove_if(observers_.begin(), observers_.end(),
            [&](const auto& obs) { return obs == observer; }),
        observers_.end()
    );
}

void CombatVisitor::notifyObservers(const std::string& attacker, const std::string& defender, bool killed) {
    for (const auto& observer : observers_) {
        observer->onCombat(attacker, defender, killed);
    }
}

void CombatVisitor::notifyDeath(const std::string& npcName) {
    for (const auto& observer : observers_) {
        observer->onDeath(npcName);
    }
}

void CombatVisitor::setOpponent(std::shared_ptr<NPC> opponent) {
    opponent_ = opponent;
    killed_ = false;
}

bool CombatVisitor::wasKilled() const {
    return killed_;
}

void CombatVisitor::visit(Orc& orc) {
    if (auto bear = std::dynamic_pointer_cast<Bear>(opponent_)) {
        killed_ = true; // Орки убивают медведей
    } else if (auto knight = std::dynamic_pointer_cast<Knight>(opponent_)) {
        killed_ = false; // Орки не убивают рыцарей
    }
    notifyObservers(orc.getName(), opponent_->getName(), killed_);
}

void CombatVisitor::visit(Knight& knight) {
    if (auto orc = std::dynamic_pointer_cast<Orc>(opponent_)) {
        killed_ = true; // Рыцари убивают Орков
    } else if (auto bear = std::dynamic_pointer_cast<Bear>(opponent_)) {
        killed_ = false; // Рыцари не убивают медведей
    }
    notifyObservers(knight.getName(), opponent_->getName(), killed_);
}

void CombatVisitor::visit(Bear& bear) {
    if (auto knight = std::dynamic_pointer_cast<Knight>(opponent_)) {
        killed_ = true; // Медведи убивают рыцарей
    } else if (auto orc = std::dynamic_pointer_cast<Orc>(opponent_)) {
        killed_ = false; // Медведи не убивают Орков
    }
    notifyObservers(bear.getName(), opponent_->getName(), killed_);
} 