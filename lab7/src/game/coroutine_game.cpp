#include "../../include/game/coroutine_game.h"
#include "../../include/factory/npc_factory.h"
#include "../../include/common/globals.h"
#include "../../include/observer/console_observer.h"
#include "../../include/observer/file_observer.h"
#include <random>
#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>

CoroutineGame::CoroutineGame() {
    // Add observers to combat visitor
    auto consoleObserver = std::make_shared<ConsoleObserver>();
    auto fileObserver = std::make_shared<FileObserver>("combat_log.txt");
    
    combat_visitor_.addObserver(consoleObserver);
    combat_visitor_.addObserver(fileObserver);
    
    initializeNPCs();
}

void CoroutineGame::initializeNPCs() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, MAP_SIZE);
    std::uniform_int_distribution<> type_dis(1, 3);
    
    for (int i = 0; i < INITIAL_NPCS; ++i) {
        std::string type;
        switch(type_dis(gen)) {
            case 1: type = "Orc"; break;
            case 2: type = "Knight"; break;
            case 3: type = "Bear"; break;
        }
        auto npc = NPCFactory::createNPC(type, "NPC_" + std::to_string(i), 
                                       dis(gen), dis(gen));
        npcs_.add(npc);
    }
}

GameTask CoroutineGame::moveAndCombat() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> angle_dis(0, 2 * M_PI);
    
    while (running_) {
        auto npcs = npcs_.getAliveNPCs();
        
        // Move NPCs and check for combat
        for (auto& npc : npcs) {
            if (!npc->isDead()) {
                // Move NPC
                double angle = angle_dis(gen);
                double speed = npc->getMoveSpeed();
                int new_x = static_cast<int>(npc->getX() + cos(angle) * speed);
                int new_y = static_cast<int>(npc->getY() + sin(angle) * speed);
                
                new_x = std::clamp(new_x, 0, MAP_SIZE);
                new_y = std::clamp(new_y, 0, MAP_SIZE);
                
                npc->setPosition(new_x, new_y);
                
                // Check for combat
                for (auto& other : npcs) {
                    if (other != npc && !other->isDead() && npc->isInRange(*other)) {
                        processCombat(npc, other);
                    }
                }
            }
        }
        
        co_await std::suspend_always{};
    }
}

void CoroutineGame::processCombat(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender) {
    if (!attacker->isDead() && !defender->isDead()) {
        int attack_roll = rollDice();
        int defense_roll = rollDice();
        
        combat_visitor_.setOpponent(defender);
        attacker->accept(combat_visitor_);
        
        if (combat_visitor_.wasKilled() && attack_roll > defense_roll) {
            defender->kill();
            combat_visitor_.notifyDeath(defender->getType() + " " + defender->getName());
        }
    }
}

int CoroutineGame::rollDice() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1, 6);
    return dis(gen);
}

void CoroutineGame::start() {
    running_ = true;
    auto start_time = std::chrono::steady_clock::now();
    
    // Start the movement and combat coroutine
    game_task_ = moveAndCombat();
    
    // Main thread handles display
    while (running_) {
        printMap();
        
        // Resume the game coroutine
        if (game_task_.coro && !game_task_.coro.done()) {
            game_task_.coro.resume();
        }
        
        auto current_time = std::chrono::steady_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(
            current_time - start_time).count();
            
        if (elapsed_time >= GAME_DURATION) {
            stop();
            break;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void CoroutineGame::stop() {
    running_ = false;
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "\nSurvivors:\n";
        npcs_.forEach([](auto& npc) {
            std::cout << npc->getType() << " " << npc->getName() 
                     << " at (" << npc->getX() << "," << npc->getY() << ")\n";
        });
    }
}

void CoroutineGame::printMap() {
    std::vector<std::vector<char>> map(MAP_SIZE, std::vector<char>(MAP_SIZE, '-'));
    
    npcs_.forEach([&map](auto& npc) {
        if (!npc->isDead()) {
            int x = static_cast<int>(npc->getX());
            int y = static_cast<int>(npc->getY());
            if (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE) {
                map[y][x] = npc->getType()[0];
            }
        }
    });
    
    std::lock_guard<std::mutex> lock(cout_mutex);
    std::cout << "\033[2J\033[H"; // Clear screen
    
    std::cout << std::string(MAP_SIZE + 2, '#') << '\n';
    
    for (const auto& row : map) {
        std::cout << '#';
        for (char cell : row) {
            std::cout << cell;
        }
        std::cout << "#\n";
    }
    
    std::cout << std::string(MAP_SIZE + 2, '#') << '\n';
}