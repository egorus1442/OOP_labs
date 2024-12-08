#include "../../include/npc/bear.h"
#include "../../include/visitor/combat_visitor.h"

void Bear::accept(CombatVisitor& visitor) {
    visitor.visit(*this);
} 