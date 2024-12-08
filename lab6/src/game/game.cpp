#include "../../include/game/game.h"
#include "../../include/factory/npc_factory.h"
#include "../../include/visitor/combat_visitor.h"
#include "../../include/observer/console_observer.h"
#include "../../include/observer/file_observer.h"
#include <iostream>
#include <algorithm>
#include <limits>

void Game::clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Game::createNPC(std::vector<std::shared_ptr<NPC>>& npcs) {
    std::string type, name;
    double x, y;
    
    std::cout << "\nДоступные типы NPC:\n";
    std::cout << "1. Orc\n2. Knight\n3. Bear\n";
    std::cout << "Выберите тип (1-3): ";
    int choice;
    std::cin >> choice;
    clearInput();
    
    switch(choice) {
        case 1: type = "Orc"; break;
        case 2: type = "Knight"; break;
        case 3: type = "Bear"; break;
        default: 
            std::cout << "Неверный выбор. Создание отменено.\n";
            return;
    }
    
    std::cout << "Введите имя: ";
    std::getline(std::cin, name);
    
    std::cout << "Введите координату X (0-500): ";
    std::cin >> x;
    std::cout << "Введите координату Y (0-500): ";
    std::cin >> y;
    clearInput();
    
    if (x < 0 || x > 500 || y < 0 || y > 500) {
        std::cout << "Координаты должны быть в диапазоне 0-500.\n";
        return;
    }
    
    auto npc = NPCFactory::createNPC(type, name, x, y);
    if (npc) {
        npcs.push_back(npc);
        std::cout << "NPC успешно создан!\n";
    }
}

void Game::displayNPCs(const std::vector<std::shared_ptr<NPC>>& npcs) {
    std::cout << "\nСписок всех NPC:\n";
    for (const auto& npc : npcs) {
        std::cout << "Тип: " << npc->getType() 
                 << ", Имя: " << npc->getName()
                 << ", Позиция: (" << npc->getX() 
                 << ", " << npc->getY() << ")\n";
    }
}

void Game::combatMode(std::vector<std::shared_ptr<NPC>>& npcs) {
    if (npcs.size() < 2) {
        std::cout << "Недостаточно NPC для боевого режима.\n";
        return;
    }
    
    std::cout << "Введите дальность боя: ";
    double combatRange;
    std::cin >> combatRange;
    clearInput();
    
    CombatVisitor combatVisitor;
    auto consoleObserver = std::make_shared<ConsoleObserver>();
    auto fileObserver = std::make_shared<FileObserver>("log.txt");
    
    combatVisitor.addObserver(consoleObserver);
    combatVisitor.addObserver(fileObserver);
    
    struct CombatResult {
        size_t victimIndex;
        std::string victimName;
    };
    std::vector<CombatResult> deaths;
    
    // Проводим все бои
    for (size_t i = 0; i < npcs.size(); ++i) {
        for (size_t j = i + 1; j < npcs.size(); ++j) {
            if (npcs[i]->isInRange(*npcs[j], combatRange)) {
                // Первый NPC атакует второго
                combatVisitor.setOpponent(npcs[j]);
                npcs[i]->accept(combatVisitor);
                
                if (combatVisitor.wasKilled()) {
                    deaths.push_back({j, npcs[j]->getName()});
                }
                
                // Второй NPC атакует первого
                combatVisitor.setOpponent(npcs[i]);
                npcs[j]->accept(combatVisitor);
                
                if (combatVisitor.wasKilled()) {
                    deaths.push_back({i, npcs[i]->getName()});
                }
            }
        }
    }
    
    // Сортируем индексы в обратном порядке
    std::sort(deaths.begin(), deaths.end(), 
        [](const CombatResult& a, const CombatResult& b) {
            return a.victimIndex > b.victimIndex;
        });
    
    // Удаляем погибших NPC
    for (const auto& death : deaths) {
        combatVisitor.notifyDeath(death.victimName);
        npcs.erase(npcs.begin() + death.victimIndex);
    }
} 