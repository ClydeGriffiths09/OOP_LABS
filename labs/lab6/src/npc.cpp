#include <iostream>

#include "npc.hpp"

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

