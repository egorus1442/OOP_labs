#pragma once
#include <vector>
#include <memory>
#include "../npc/npc.h"

class Game {
public:
    static void createNPC(std::vector<std::shared_ptr<NPC>>& npcs);
    static void displayNPCs(const std::vector<std::shared_ptr<NPC>>& npcs);
    static void combatMode(std::vector<std::shared_ptr<NPC>>& npcs);
    static void clearInput();
}; 