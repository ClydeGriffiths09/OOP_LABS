#include <fstream>
#include <iostream>

#include "npc_handle.hpp"
#include "npc_factory.hpp"

void NPCHandler::AddNPC(std::shared_ptr<NPC> npc) {
    npcs.push_back(std::move(npc));
}

void NPCHandler::PrintAll() const {
    if (npcs.empty()) {
        std::cout << "No NPCs in the dungeon.\n";
        return;
    }
    for (const auto& npc : npcs) {
        npc->Print();
    }
}

void NPCHandler::SaveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Cannot open file for saving: " << filename << std::endl;
        return;
    }

    for (const auto& npc : npcs) {
        NPCFactory::SaveNPC(file, npc);
    }
}

void NPCHandler::LoadFromFile(const std::string& filename) {
    npcs.clear();
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "File not found: " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            try {
                auto npc = NPCFactory::LoadNPC(line);
                npcs.push_back(npc);
            } catch (const std::exception& e) {
                std::cerr << "Error loading NPC: " << e.what() << " (line: " << line << ")\n";
            }
        }
    }
}