#pragma once

#include <string>
#include <memory>

class BattleVisitor;

class NPC {
private:
    double x;
    double y;
    std::string type;
    std::string name;

public:
    NPC(double x, double y, const std::string& name, const std::string& type);
    virtual ~NPC() = default;

    double GetX() const;
    double GetY() const;
    const std::string& GetName() const;
    const std::string& GetType() const;

    virtual void Accept(BattleVisitor& visitor, std::shared_ptr<NPC> other) = 0;
    virtual bool Fight(std::shared_ptr<NPC> other) = 0;
    virtual void Print() const;
};