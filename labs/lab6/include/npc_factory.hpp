#pragma once

#include <memory>
#include <string>

#include "npc.hpp"

class NPCFactory {
public:
    static std::shared_ptr<NPC> CreateNPC(const std::string& type, double x, double y, const std::string& name);
    static std::shared_ptr<NPC> LoadNPC(const std::string& line);
    static void SaveNPC(std::ostream& os, const std::shared_ptr<NPC>& npc);
};
