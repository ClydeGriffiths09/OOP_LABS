#include "squirrel.hpp"
#include "battle_visitor.hpp"
#include "pegasus.hpp"
#include <memory>

Squirrel::Squirrel(double x, double y, const std::string& name)
    : NPC(x, y, name, "Squirrel") {}

void Squirrel::Accept(BattleVisitor& visitor, std::shared_ptr<NPC> other) {
    visitor.Visit(*this, other);
}

bool Squirrel::Fight(std::shared_ptr<NPC> other) {
    return dynamic_cast<Pegasus*>(other.get()) != nullptr;
}