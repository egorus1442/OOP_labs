#include <iostream>
#include <vector>
#include <memory>
#include "../include/factory/npc_factory.h"
#include "../include/game/game.h"

void printMenu() {
    std::cout << "\nBalagur Fate 3 - Редактор подземелий\n";
    std::cout << "1. Добавить нового NPC\n";
    std::cout << "2. Загрузить NPC из файла\n";
    std::cout << "3. Показать всех NPC\n";
    std::cout << "4. Начать боевой режим\n";
    std::cout << "5. Сохранить и выйти\n";
    std::cout << "Выберите действие: ";
}

int main() {
    std::vector<std::shared_ptr<NPC>> npcs;
    std::string filename = "npcs.txt";
    int choice;
    
    while (true) {
        printMenu();
        std::cin >> choice;
        Game::clearInput();
        
        switch(choice) {
            case 1: {
                Game::createNPC(npcs);
                break;
            }
            case 2: {
                std::cout << "Введите имя файла: ";
                std::string loadFile;
                std::getline(std::cin, loadFile);
                auto loadedNPCs = NPCFactory::loadFromFile(loadFile);
                npcs = loadedNPCs;
                std::cout << "NPC загружены из файла.\n";
                break;
            }
            case 3: {
                Game::displayNPCs(npcs);
                break;
            }
            case 4: {
                Game::combatMode(npcs);
                break;
            }
            case 5: {
                NPCFactory::saveToFile(npcs, filename);
                std::cout << "NPC сохранены в " << filename << "\nДо свидания!\n";
                return 0;
            }
            default: {
                std::cout << "Неверный выбор. Попробуйте снова.\n";
            }
        }
    }
    
    return 0;
} 