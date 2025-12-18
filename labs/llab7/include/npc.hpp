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
    bool alive = true;

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

    bool IsAlive() const {return alive;}
    void Kill() {alive = false;}

    void Move(double dx, double dy, double map_size = 100.0);
};

class Knight: public NPC {
public:
    Knight(double x, double y, const std::string& name);
    void Accept(BattleVisitor& visitor, std::shared_ptr<NPC> other) override;
    bool Fight(std::shared_ptr<NPC> other) override;
};

class Pegasus: public NPC {
public:
    Pegasus(double x, double y, const std::string& name);
    void Accept(BattleVisitor& visitor, std::shared_ptr<NPC> other) override;
    bool Fight(std::shared_ptr<NPC> other) override;
};

class Squirrel: public NPC {
public:
    Squirrel(double x, double y, const std::string& name);
    void Accept(BattleVisitor& visitor, std::shared_ptr<NPC> other) override;
    bool Fight(std::shared_ptr<NPC> other) override;
};