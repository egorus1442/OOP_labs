#include "../../include/game/thread_safe_container.h"
#include <mutex>
#include <shared_mutex>

void ThreadSafeContainer::add(std::shared_ptr<NPC> npc) {
    std::unique_lock lock(mutex_);
    npcs_.push_back(npc);
}

void ThreadSafeContainer::remove(size_t index) {
    std::unique_lock lock(mutex_);
    if (index < npcs_.size()) {
        npcs_.erase(npcs_.begin() + index);
    }
}

std::vector<std::shared_ptr<NPC>> ThreadSafeContainer::getAliveNPCs() {
    std::shared_lock lock(mutex_);
    std::vector<std::shared_ptr<NPC>> alive;
    for (auto& npc : npcs_) {
        if (npc && !npc->isDead()) {
            alive.push_back(npc);
        }
    }
    return alive;
}

void ThreadSafeContainer::updatePosition(size_t index, double x, double y) {
    std::unique_lock lock(mutex_);
    if (index < npcs_.size() && npcs_[index]) {
        npcs_[index]->setPosition(x, y);
    }
}

size_t ThreadSafeContainer::size() const {
    std::shared_lock lock(mutex_);
    return npcs_.size();
} 