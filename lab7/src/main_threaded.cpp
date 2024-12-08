#include <iostream>
#include <thread>
#include <chrono>
#include "../include/game/game.h"

void displayGameInfo() {
    std::cout << "\n=== Balagur Fate 3: Battle Royale (Threaded Version) ===\n";
    std::cout << "Map Size: 100x100\n";
    std::cout << "Initial NPCs: 50\n";
    std::cout << "Game Duration: 30 seconds\n";
    std::cout << "\nNPC Types and Properties:\n";
    std::cout << "- Orc: Movement Speed 20, Combat Range 10\n";
    std::cout << "- Knight: Movement Speed 30, Combat Range 10\n";
    std::cout << "- Bear: Movement Speed 5, Combat Range 10\n";
    std::cout << "\nCombat Rules:\n";
    std::cout << "- Orcs kill Bears\n";
    std::cout << "- Knights kill Orcs\n";
    std::cout << "- Bears kill Knights\n";
    std::cout << "- Combat resolved with 6-sided dice rolls\n";
    std::cout << "\nStarting battle in 3 seconds...\n";
    std::cout << "=================================\n\n";
}

int main() {
    displayGameInfo();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    
    Game game;
    game.start();
    
    return 0;
} 