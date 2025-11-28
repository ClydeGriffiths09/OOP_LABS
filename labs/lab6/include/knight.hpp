#pragma once

#include "npc.hpp"

class BattleVisitor;

class Knight: public NPC {
public:
    Knight(double x, double y, const std::string& name);
    void Accept(BattleVisitor& visitor, std::shared_ptr<NPC> other) override;
    bool Fight(std::shared_ptr<NPC> other) override;
};