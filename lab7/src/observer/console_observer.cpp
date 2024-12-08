#include "../../include/observer/console_observer.h"
#include "../../include/common/globals.h"
#include <iostream>

void ConsoleObserver::onCombat(const std::string& attacker, const std::string& defender, bool killed) {
    std::lock_guard<std::mutex> lock(cout_mutex);
    if (killed) {
        std::cout << attacker << " атаковал " << defender;
        std::cout << " и нанес смертельный удар!";
        std::cout << std::endl;
    }
}

void ConsoleObserver::onDeath(const std::string& npcName) {
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << npcName << " погиб в бою!\n";
} 