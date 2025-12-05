#pragma once

#include "npc_handle.hpp"
#include "battle_visitor.hpp"
#include "observer.hpp"

class DungeonEditor {
private:
    NPCHandler handler;

public:
    void Run();
};