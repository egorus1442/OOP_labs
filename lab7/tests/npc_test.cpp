#include <gtest/gtest.h>
#include "../include/npc/orc.h"
#include "../include/npc/knight.h"
#include "../include/npc/bear.h"
#include <memory>

TEST(NPCTest, Creation) {
    auto orc = std::make_shared<Orc>();
    auto knight = std::make_shared<Knight>();
    auto bear = std::make_shared<Bear>();
    
    orc->setName("Thrall");
    knight->setName("Arthur");
    bear->setName("Mishka");
    
    EXPECT_EQ(orc->getName(), "Thrall");
    EXPECT_EQ(knight->getName(), "Arthur");
    EXPECT_EQ(bear->getName(), "Mishka");
    
    EXPECT_EQ(orc->getType(), "Orc");
    EXPECT_EQ(knight->getType(), "Knight");
    EXPECT_EQ(bear->getType(), "Bear");
}

TEST(NPCTest, Position) {
    auto orc = std::make_shared<Orc>();
    orc->setPosition(10, 20);
    
    EXPECT_EQ(orc->getX(), 10);
    EXPECT_EQ(orc->getY(), 20);
}

TEST(NPCTest, Range) {
    auto orc1 = std::make_shared<Orc>();
    auto orc2 = std::make_shared<Orc>();
    orc1->setPosition(0, 0);
    orc2->setPosition(3, 4);
    
    EXPECT_TRUE(orc1->isInRange(*orc2));  // Default range is 10
    
    orc2->setPosition(15, 15);
    EXPECT_FALSE(orc1->isInRange(*orc2)); // Out of range
}

TEST(NPCTest, Movement) {
    auto knight = std::make_shared<Knight>();
    EXPECT_EQ(knight->getMoveSpeed(), 30);
    
    auto orc = std::make_shared<Orc>();
    EXPECT_EQ(orc->getMoveSpeed(), 20);
    
    auto bear = std::make_shared<Bear>();
    EXPECT_EQ(bear->getMoveSpeed(), 5);
} 