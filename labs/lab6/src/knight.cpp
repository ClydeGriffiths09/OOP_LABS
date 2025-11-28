#include "knight.hpp"
#include "battle_visitor.hpp"
#include "squirrel.hpp"
#include <memory>

Knight::Knight(double x, double y, const std::string& name)
    : NPC(x, y, name, "Knight") {}

void Knight::Accept(BattleVisitor& visitor, std::shared_ptr<NPC> other) {
    visitor.Visit(*this, other);
}

bool Knight::Fight(std::shared_ptr<NPC> other) {
    return dynamic_cast<Squirrel*>(other.get()) != nullptr;
}
