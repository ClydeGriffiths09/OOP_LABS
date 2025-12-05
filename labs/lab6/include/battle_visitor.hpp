#pragma once

#include <vector>
#include <memory>

#include "observer.hpp"

class Knight;
class Squirrel;
class Pegasus;
class NPC;

class BattleVisitor {
public:
    virtual void Visit(Knight& attacker, std::shared_ptr<NPC> defender) = 0;
    virtual void Visit(Pegasus& attacker, std::shared_ptr<NPC> defender) = 0;
    virtual void Visit(Squirrel& attacker, std::shared_ptr<NPC> defender) = 0;

    virtual ~BattleVisitor() = default;
};

class BattleSystem : public BattleVisitor {
private:
    std::vector<std::shared_ptr<Observer>> observers;
    const double range;

    double Distance(const NPC& a, const NPC& b) const;
    void Notify(const std::string& message);

public:
    explicit BattleSystem(double range);
    
    void AddObserver(std::shared_ptr<Observer> obs);
    
    void Visit(Knight& attacker, std::shared_ptr<NPC> defender) override;
    void Visit(Pegasus& attacker, std::shared_ptr<NPC> defender) override;
    void Visit(Squirrel& attacker, std::shared_ptr<NPC> defender) override;
    
    virtual ~BattleSystem() = default;
};