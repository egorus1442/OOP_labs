#include <gtest/gtest.h>
#include "../include/visitor/combat_visitor.h"
#include "../include/npc/orc.h"
#include "../include/npc/knight.h"
#include "../include/npc/bear.h"
#include "../include/observer/console_observer.h"
#include <memory>

class TestObserver : public CombatObserver {
public:
    void onCombat(const std::string& attacker, const std::string& defender, bool killed) override {
        lastAttacker = attacker;
        lastDefender = defender;
        lastKilled = killed;
    }
    
    void onDeath(const std::string& npcName) override {
        lastDeath = npcName;
    }
    
    std::string lastAttacker, lastDefender, lastDeath;
    bool lastKilled = false;
};

TEST(CombatTest, OrcVsKnight) {
    auto orc = std::make_shared<Orc>();
    auto knight = std::make_shared<Knight>();
    orc->setName("Thrall");
    knight->setName("Arthur");
    
    auto testObserver = std::make_shared<TestObserver>();
    CombatVisitor visitor;
    visitor.addObserver(testObserver);
    
    visitor.setOpponent(knight);
    orc->accept(visitor);
    
    EXPECT_EQ(testObserver->lastAttacker, "Thrall");
    EXPECT_EQ(testObserver->lastDefender, "Arthur");
    EXPECT_FALSE(testObserver->lastKilled);
}

TEST(CombatTest, KnightVsOrc) {
    auto knight = std::make_shared<Knight>();
    auto orc = std::make_shared<Orc>();
    knight->setName("Arthur");
    orc->setName("Thrall");
    
    auto testObserver = std::make_shared<TestObserver>();
    CombatVisitor visitor;
    visitor.addObserver(testObserver);
    
    visitor.setOpponent(orc);
    knight->accept(visitor);
    
    EXPECT_EQ(testObserver->lastAttacker, "Arthur");
    EXPECT_EQ(testObserver->lastDefender, "Thrall");
    EXPECT_TRUE(testObserver->lastKilled);
}

TEST(CombatTest, BearVsKnight) {
    auto bear = std::make_shared<Bear>();
    auto knight = std::make_shared<Knight>();
    bear->setName("Mishka");
    knight->setName("Arthur");
    
    auto testObserver = std::make_shared<TestObserver>();
    CombatVisitor visitor;
    visitor.addObserver(testObserver);
    
    visitor.setOpponent(knight);
    bear->accept(visitor);
    
    EXPECT_EQ(testObserver->lastAttacker, "Mishka");
    EXPECT_EQ(testObserver->lastDefender, "Arthur");
    EXPECT_TRUE(testObserver->lastKilled);
} 