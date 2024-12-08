#include <gtest/gtest.h>
#include "../include/factory/npc_factory.h"
#include <fstream>

TEST(FactoryTest, CreateNPC) {
    auto orc = NPCFactory::createNPC("Orc", "Thrall", 10, 20);
    ASSERT_NE(orc, nullptr);
    EXPECT_EQ(orc->getType(), "Orc");
    EXPECT_EQ(orc->getName(), "Thrall");
    EXPECT_EQ(orc->getX(), 10);
    EXPECT_EQ(orc->getY(), 20);
    
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