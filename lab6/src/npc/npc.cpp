#include "../../include/npc/npc.h"
#include <cmath>

bool NPC::isInRange(const NPC& other, double range) const {
    double dx = x_ - other.x_;
    double dy = y_ - other.y_;
    return std::sqrt(dx*dx + dy*dy) <= range;
}

void NPC::setPosition(double x, double y) {
    x_ = x;
    y_ = y;
}

void NPC::setName(const std::string& name) {
    name_ = name;
}

double NPC::getX() const { return x_; }
double NPC::getY() const { return y_; }
std::string NPC::getName() const { return name_; } 