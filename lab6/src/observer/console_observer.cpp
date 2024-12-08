#include "../../include/observer/console_observer.h"
#include <iostream>

void ConsoleObserver::onCombat(const std::string& attacker, const std::string& defender, bool killed) {
    std::cout << attacker << " атаковал " << defender;
    if (killed) {
        std::cout << " и нанес смертельный удар!";
    }
    std::cout << std::endl;
}

void ConsoleObserver::onDeath(const std::string& npcName) {
    std::cout << npcName << " погиб в бою!\n";
} 