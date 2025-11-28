#pragma once

#include <vector>
#include <memory>

#include "observer.hpp"

class Knight;
class Squirrel;
class Pegasus;
class NPC;

class BattleVisitor {
private:
    std::vector<std::shared_ptr<Observer>> observers;
    const double range;

public:
    BattleVisitor(double range);
    void AddObserver(std::shared_ptr<Observer> obs);

    void Visit(Knight& attacker, std::shared_ptr<NPC> defender);
    void Visit(Pegasus& attacker, std::shared_ptr<NPC> defender);
    void Visit(Squirrel& attacker, std::shared_ptr<NPC> defender);

    double Distance(const NPC& a, const NPC& b) const;
    void Notify(const std::string& message);
};