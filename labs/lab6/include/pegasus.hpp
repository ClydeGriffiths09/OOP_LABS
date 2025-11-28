#pragma once

#include "npc.hpp"

class BattleVisitor;

class Pegasus: public NPC {
public:
    Pegasus(double x, double y, const std::string& name);
    void Accept(BattleVisitor& visitor, std::shared_ptr<NPC> other) override;
    bool Fight(std::shared_ptr<NPC> other) override;
};