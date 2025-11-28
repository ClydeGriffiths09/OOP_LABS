#include "pegasus.hpp"
#include "battle_visitor.hpp"

Pegasus::Pegasus(double x, double y, const std::string& name)
    : NPC(x, y, name, "Pegasus") {}

void Pegasus::Accept(BattleVisitor& visitor, std::shared_ptr<NPC> other) {
    visitor.Visit(*this, other);
}

bool Pegasus::Fight(std::shared_ptr<NPC> other) {
    return false;
}