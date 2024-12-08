#include "../../include/observer/file_observer.h"

FileObserver::FileObserver(const std::string& filename) {
    file_.open(filename, std::ios::app);
}

void FileObserver::onCombat(const std::string& attacker, const std::string& defender, bool killed) {
    if (file_.is_open()) {
        file_ << attacker << " атаковал " << defender;
        if (killed) {
            file_ << " и нанес смертельный удар!";
        }
        file_ << std::endl;
    }
}

void FileObserver::onDeath(const std::string& npcName) {
    if (file_.is_open()) {
        file_ << npcName << " погиб в бою!\n";
    }
} 