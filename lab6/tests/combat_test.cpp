#include <gtest/gtest.h>
#include "../include/visitor/combat_visitor.h"
#include "../include/npc/orc.h"
#include "../include/npc/knight.h"
#include "../include/npc/bear.h"
#include "../include/observer/console_observer.h"

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
    Orc orc;
    Knight knight;
    orc.setName("Thrall");
    knight.setName("Arthur");
    
    auto testObserver = std::make_shared<TestObserver>();
    CombatVisitor visitor;
    visitor.addObserver(testObserver);
    
    // Orc attacks Knight
    visitor.setOpponent(std::make_shared<Knight>(knight));
    orc.accept(visitor);
    
    EXPECT_EQ(testObserver->lastAttacker, "Thrall");
    EXPECT_EQ(testObserver->lastDefender, "Arthur");
    EXPECT_FALSE(testObserver->lastKilled); // Орк не может убить рыцаря
}

TEST(CombatTest, KnightVsOrc) {
    Knight knight;
    Orc orc;
    knight.setName("Arthur");
    orc.setName("Thrall");
    
    auto testObserver = std::make_shared<TestObserver>();
    CombatVisitor visitor;
    visitor.addObserver(testObserver);
    
    visitor.setOpponent(std::make_shared<Orc>(orc));
    knight.accept(visitor);
    
    EXPECT_EQ(testObserver->lastAttacker, "Arthur");
    EXPECT_EQ(testObserver->lastDefender, "Thrall");
    EXPECT_TRUE(testObserver->lastKilled); // Рыцарь убивает орка
} 