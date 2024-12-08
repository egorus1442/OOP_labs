#pragma once
#include <vector>
#include <memory>
#include <thread>
#include <queue>
#include <mutex>
#include <algorithm>
#include "../npc/npc.h"
#include "../visitor/combat_visitor.h"
#include "thread_safe_container.h"

class Game {
public:
    Game();
    void start();
    void stop();

private:
    static constexpr int MAP_SIZE = 100;
    static constexpr int INITIAL_NPCS = 50;
    static constexpr int GAME_DURATION = 30;
    
    void movementThread();
    void combatThread();
    void printMap();
    
    int rollDice();
    void initializeNPCs();
    
    ThreadSafeContainer npcs_;
    std::atomic<bool> running_{false};
    std::mutex combat_mutex_;
    std::queue<std::pair<std::shared_ptr<NPC>, std::shared_ptr<NPC>>> combat_queue_;
    
    std::thread movement_thread_;
    std::thread combat_thread_;
}; 