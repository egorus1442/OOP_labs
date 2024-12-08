#pragma once
#include <vector>
#include <shared_mutex>
#include <memory>
#include "../npc/npc.h"

class ThreadSafeContainer {
public:
    void add(std::shared_ptr<NPC> npc);
    void remove(size_t index);
    std::vector<std::shared_ptr<NPC>> getAliveNPCs();
    void updatePosition(size_t index, double x, double y);
    size_t size() const;
    
    template<typename Func>
    void forEach(Func f) {
        std::shared_lock lock(mutex_);
        for (auto& npc : npcs_) {
            if (npc && !npc->isDead()) {
                f(npc);
            }
        }
    }

private:
    std::vector<std::shared_ptr<NPC>> npcs_;
    mutable std::shared_mutex mutex_;
}; 