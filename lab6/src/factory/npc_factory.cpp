#include "../../include/factory/npc_factory.h"
#include "../../include/npc/orc.h"
#include "../../include/npc/knight.h"
#include "../../include/npc/bear.h"
#include <fstream>
#include <sstream>

std::shared_ptr<NPC> NPCFactory::createNPC(const std::string& type, const std::string& name, double x, double y) {
    std::shared_ptr<NPC> npc = nullptr;
    
    if (type == "Orc") {
        npc = std::make_shared<Orc>();
    } else if (type == "Knight") {
        npc = std::make_shared<Knight>();
    } else if (type == "Bear") {
        npc = std::make_shared<Bear>();
    }
    
    if (npc) {
        npc->setName(name);
        npc->setPosition(x, y);
    }
    
    return npc;
}

void NPCFactory::saveToFile(const std::vector<std::shared_ptr<NPC>>& npcs, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) return;

    for (const auto& npc : npcs) {
        file << npc->getType() << " "
             << npc->getName() << " "
             << npc->getX() << " "
             << npc->getY() << "\n";
    }
}

std::vector<std::shared_ptr<NPC>> NPCFactory::loadFromFile(const std::string& filename) {
    std::vector<std::shared_ptr<NPC>> npcs;
    std::ifstream file(filename);
    if (!file) return npcs;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type, name;
        double x, y;
        
        if (iss >> type >> name >> x >> y) {
            auto npc = createNPC(type, name, x, y);
            if (npc) {
                npcs.push_back(npc);
            }
        }
    }
    
    return npcs;
} 