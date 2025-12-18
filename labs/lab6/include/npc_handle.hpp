#pragma once

#include <vector>
#include <memory>

#include "npc.hpp"

class NPCHandler {
private:
    std::vector<std::shared_ptr<NPC>> npcs;

public:
    void AddNPC(std::shared_ptr<NPC> npc);
    void PrintAll() const;
    void SaveToFile(const std::string& filename) const;
    void LoadFromFile(const std::string& filename);
    
    const std::vector<std::shared_ptr<NPC>>& GetNPCs() const { return npcs; }
};