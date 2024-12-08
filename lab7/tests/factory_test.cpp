#include <gtest/gtest.h>
#include "../include/factory/npc_factory.h"
#include "../include/common/globals.h"
#include <fstream>

TEST(FactoryTest, CreateNPC) {
    auto orc = NPCFactory::createNPC("Orc", "Thrall", 10, 20);
    ASSERT_NE(orc, nullptr);
    EXPECT_EQ(orc->getType(), "Orc");
    EXPECT_EQ(orc->getName(), "Thrall");
    EXPECT_EQ(orc->getX(), 10);
    EXPECT_EQ(orc->getY(), 20);
    EXPECT_EQ(orc->getMoveSpeed(), 20);
    
    auto knight = NPCFactory::createNPC("Knight", "Arthur", 30, 40);
    ASSERT_NE(knight, nullptr);
    EXPECT_EQ(knight->getMoveSpeed(), 30);
    
    auto bear = NPCFactory::createNPC("Bear", "Mishka", 50, 60);
    ASSERT_NE(bear, nullptr);
    EXPECT_EQ(bear->getMoveSpeed(), 5);
    
    auto invalid = NPCFactory::createNPC("Invalid", "Test", 0, 0);
    EXPECT_EQ(invalid, nullptr);
}

TEST(FactoryTest, SaveAndLoad) {
    std::vector<std::shared_ptr<NPC>> npcs;
    npcs.push_back(NPCFactory::createNPC("Orc", "Thrall", 10, 20));
    npcs.push_back(NPCFactory::createNPC("Knight", "Arthur", 30, 40));
    
    std::string testFile = "test_npcs.txt";
    NPCFactory::saveToFile(npcs, testFile);
    
    auto loadedNpcs = NPCFactory::loadFromFile(testFile);
    ASSERT_EQ(loadedNpcs.size(), 2);
    
    EXPECT_EQ(loadedNpcs[0]->getType(), "Orc");
    EXPECT_EQ(loadedNpcs[0]->getName(), "Thrall");
    EXPECT_EQ(loadedNpcs[1]->getType(), "Knight");
    EXPECT_EQ(loadedNpcs[1]->getName(), "Arthur");
    
    std::remove(testFile.c_str());
} 