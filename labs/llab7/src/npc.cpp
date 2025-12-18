#include <iostream>
#include <algorithm>

#include "npc.hpp"
#include "battle_visitor.hpp"

// class NPC
NPC::NPC(double x, double y, const std::string& name, const std::string& type) 
    : x(x), y(y), name(name), type(type) {}

double NPC::GetX() const {
    return x;
}

double NPC::GetY() const {
    return y;
}

const std::string& NPC::GetName() const {
    return name;
}

const std::string& NPC::GetType() const {
    return type;
}

void NPC::Print() const {
    std::cout << type << " [" << name << "] at (" << x << ", " << y << ")" << std::endl;
}

void NPC::Move(double dx, double dy, double map_size) {
    x = std::clamp(x + dx, 0.0, map_size - 1.0);
    y = std::clamp(y + dy, 0.0, map_size - 1.0);
}

// class Knight
Knight::Knight(double x, double y, const std::string& name)
    : NPC(x, y, name, "Knight") {}

void Knight::Accept(BattleVisitor& visitor, std::shared_ptr<NPC> other) {
    visitor.Visit(*this, other);
}

bool Knight::Fight(std::shared_ptr<NPC> other) {
    return dynamic_cast<Squirrel*>(other.get()) != nullptr;
}

// class Squirrel 
Squirrel::Squirrel(double x, double y, const std::string& name)
    : NPC(x, y, name, "Squirrel") {}

void Squirrel::Accept(BattleVisitor& visitor, std::shared_ptr<NPC> other) {
    visitor.Visit(*this, other);
}

bool Squirrel::Fight(std::shared_ptr<NPC> other) {
    return dynamic_cast<Pegasus*>(other.get()) != nullptr;
}

// class Pegasus
Pegasus::Pegasus(double x, double y, const std::string& name)
    : NPC(x, y, name, "Pegasus") {}

void Pegasus::Accept(BattleVisitor& visitor, std::shared_ptr<NPC> other) {
    visitor.Visit(*this, other);
}

bool Pegasus::Fight(std::shared_ptr<NPC> other) {
    return false;
}

