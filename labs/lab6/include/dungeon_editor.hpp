#pragma once

#include "npc_handle.hpp"
#include "battle_visitor.hpp"
#include "console_observer.hpp"
#include "file_observer.hpp"

class DungeonEditor {
private:
    NPCHandler handler;

public:
    void Run();
};