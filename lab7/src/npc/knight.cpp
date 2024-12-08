#include "../../include/npc/knight.h"
#include "../../include/visitor/combat_visitor.h"

void Knight::accept(CombatVisitor& visitor) {
    visitor.visit(*this);
} 