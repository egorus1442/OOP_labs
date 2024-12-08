#include "../../include/npc/orc.h"
#include "../../include/visitor/combat_visitor.h"

void Orc::accept(CombatVisitor& visitor) {
    visitor.visit(*this);
} 