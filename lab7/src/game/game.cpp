#include "../../include/game/game.h"
#include "../../include/factory/npc_factory.h"
#include "../../include/visitor/combat_visitor.h"
#include "../../include/observer/console_observer.h"
#include "../../include/observer/file_observer.h"
#include "../../include/common/globals.h"
#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <queue>
#include <cmath>
#include <algorithm>
#include <limits>

Game::Game() {
    initializeNPCs();
}

void Game::initializeNPCs() {
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

int Game::rollDice() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1, 6);
    return dis(gen);
}

void Game::start() {
    running_ = true;
    movement_thread_ = std::thread(&Game::movementThread, this);
    combat_thread_ = std::thread(&Game::combatThread, this);
    
    // Start time measurement
    auto start_time = std::chrono::steady_clock::now();
    
    // Run display in main thread
    while (running_) {
        printMap();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        // Check if game duration has elapsed
        auto current_time = std::chrono::steady_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(
            current_time - start_time).count();
            
        if (elapsed_time >= GAME_DURATION) {
            stop();
        }
    }
}

void Game::stop() {
    running_ = false;
    if (movement_thread_.joinable()) movement_thread_.join();
    if (combat_thread_.joinable()) combat_thread_.join();
    
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "\nSurvivors:\n";
        npcs_.forEach([](auto& npc) {
            std::cout << npc->getType() << " " << npc->getName() 
                     << " at (" << npc->getX() << "," << npc->getY() << ")\n";
        });
    }
}

void Game::movementThread() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> angle_dis(0, 2 * M_PI);
    
    while (running_) {
        auto npcs = npcs_.getAliveNPCs();
        for (size_t i = 0; i < npcs.size(); ++i) {
            if (!npcs[i]->isDead()) {
                // Calculate new position
                double angle = angle_dis(gen);
                double speed = npcs[i]->getMoveSpeed();
                int new_x = static_cast<int>(npcs[i]->getX() + cos(angle) * speed);
                int new_y = static_cast<int>(npcs[i]->getY() + sin(angle) * speed);
                
                // Keep within bounds
                new_x = std::clamp(new_x, 0, MAP_SIZE);
                new_y = std::clamp(new_y, 0, MAP_SIZE);
                
                npcs[i]->setPosition(new_x, new_y);
                
                // Check for combat with other NPCs
                for (size_t j = i + 1; j < npcs.size(); ++j) {
                    if (!npcs[j]->isDead() && npcs[i]->isInRange(*npcs[j])) {
                        // Create combat task
                        std::lock_guard<std::mutex> lock(combat_mutex_);
                        combat_queue_.push({npcs[i], npcs[j]});
                    }
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void Game::combatThread() {
    CombatVisitor visitor;
    auto consoleObserver = std::make_shared<ConsoleObserver>();
    auto fileObserver = std::make_shared<FileObserver>("combat_log.txt");
    
    visitor.addObserver(consoleObserver);
    visitor.addObserver(fileObserver);
    
    while (running_) {
        std::vector<std::pair<std::shared_ptr<NPC>, std::shared_ptr<NPC>>> battles;
        std::vector<std::shared_ptr<NPC>> to_kill;
        
        // Get all battles from queue
        {
            std::lock_guard<std::mutex> lock(combat_mutex_);
            while (!combat_queue_.empty()) {
                battles.push_back(combat_queue_.front());
                combat_queue_.pop();
            }
        }
        
        // Process all battles
        for (const auto& [attacker, defender] : battles) {
            if (!attacker->isDead() && !defender->isDead()) {
                int attack_roll = rollDice();
                int defense_roll = rollDice();
                
                visitor.setOpponent(defender);
                attacker->accept(visitor);
                
                if (visitor.wasKilled() && attack_roll > defense_roll) {
                    to_kill.push_back(defender);
                }
            }
        }
        
        // Resolve deaths after all battles
        for (const auto& npc : to_kill) {
            npc->kill();
            visitor.notifyDeath(npc->getType() + " " + npc->getName());
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}

void Game::printMap() {
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
    
    // Print top border
    std::cout << std::string(MAP_SIZE + 2, '#') << '\n';
    
    // Print map with side borders
    for (const auto& row : map) {
        std::cout << '#';
        for (char cell : row) {
            std::cout << cell;
        }
        std::cout << '#' << '\n';
    }
    
    // Print bottom border
    std::cout << std::string(MAP_SIZE + 2, '#') << '\n';
}