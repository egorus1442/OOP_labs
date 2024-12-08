#pragma once
#include <memory>
#include <vector>
#include "../npc/npc.h"

class NPCFactory {
public:
    static std::shared_ptr<NPC> createNPC(const std::string& type, const std::string& name, double x, double y);
    static std::vector<std::shared_ptr<NPC>> loadFromFile(const std::string& filename);
    static void saveToFile(const std::vector<std::shared_ptr<NPC>>& npcs, const std::string& filename);
}; 