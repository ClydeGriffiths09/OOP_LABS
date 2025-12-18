#include <sstream>
#include <stdexcept>

#include "npc_factory.hpp"
#include "npc.hpp"

std::shared_ptr<NPC> NPCFactory::CreateNPC(const std::string& type, double x, double y, const std::string& name) {
    if (x < 0 || x > 500 || y < 0 || y > 500) {
        throw std::invalid_argument("Coordinates must be in [0, 500]");
    }

    if (type == "Knight") {
        return std::make_shared<Knight>(x, y, name);
    } else if (type == "Squirrel") {
        return std::make_shared<Squirrel>(x, y, name);
    } else if (type == "Pegasus") {
        return std::make_shared<Pegasus>(x, y, name);
    } else {
        throw std::invalid_argument("Unknown NPC type: " + type);
    }
}

std::shared_ptr<NPC> NPCFactory::LoadNPC(const std::string& line) {
    std::istringstream iss(line);
    std::string type, name;
    double x, y;
    char comma;

    if (!std::getline(iss, type, ',') || !(iss >> x) || !(iss >> comma) || !(iss >> y) || !(iss >> comma)) {
        throw std::runtime_error("Invalid format in line: " + line);
    }
    std::getline(iss, name);
    
    return CreateNPC(type, x, y, name);
}

void NPCFactory::SaveNPC(std::ostream& os, const std::shared_ptr<NPC>& npc) {
    os << npc->GetType() << "," << npc->GetX() << "," << npc->GetY() << "," << npc->GetName() << "\n";
}