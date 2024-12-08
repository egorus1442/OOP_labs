#include <gtest/gtest.h>
#include "../include/npc/orc.h"
#include "../include/npc/knight.h"
#include "../include/npc/bear.h"

TEST(NPCTest, Creation) {
    Orc orc;
    Knight knight;
    Bear bear;
    
    orc.setName("Thrall");
    knight.setName("Arthur");
    bear.setName("Mishka");
    
    EXPECT_EQ(orc.getName(), "Thrall");
    EXPECT_EQ(knight.getName(), "Arthur");
    EXPECT_EQ(bear.getName(), "Mishka");
    
    EXPECT_EQ(orc.getType(), "Orc");
    EXPECT_EQ(knight.getType(), "Knight");
    EXPECT_EQ(bear.getType(), "Bear");
}

TEST(NPCTest, Position) {
    Orc orc;
    orc.setPosition(10, 20);
    
    EXPECT_EQ(orc.getX(), 10);
    EXPECT_EQ(orc.getY(), 20);
}

TEST(NPCTest, Range) {
    Orc orc1, orc2;
    orc1.setPosition(0, 0);
    orc2.setPosition(3, 4);
    
    // Distance should be 5 (3-4-5 triangle)
    EXPECT_TRUE(orc1.isInRange(orc2, 6));  // In range
    EXPECT_FALSE(orc1.isInRange(orc2, 4)); // Out of range
} 