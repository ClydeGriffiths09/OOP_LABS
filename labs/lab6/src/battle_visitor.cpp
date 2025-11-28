#include <cmath>
#include <sstream>

#include "battle_visitor.hpp"
#include "knight.hpp"
#include "squirrel.hpp"
#include "pegasus.hpp"

BattleVisitor::BattleVisitor(double range): range(range) {}

void BattleVisitor::AddObserver(std::shared_ptr<Observer> obs) {
    observers.push_back(std::move(obs));
}

void BattleVisitor::Visit(Knight& attacker, std::shared_ptr<NPC> defender) {
    if (Distance(attacker, *defender) <= range) {
        if (attacker.Fight(defender)) {
            std::ostringstream oss;
            oss << attacker.GetName() << " (Knight) killed " << defender->GetName() << " (" 
            << defender->GetType() << ")";
            Notify(oss.str()); 
        }
    }
}

void BattleVisitor::Visit(Squirrel& attacker, std::shared_ptr<NPC> defender) {
    if (Distance(attacker, *defender) <= range) {
        if (attacker.Fight(defender)) {
            std::ostringstream oss;
            oss << attacker.GetName() << " (Squirrel) killed " << defender->GetName() << " (" 
            << defender->GetType() << ")";
            Notify(oss.str()); 
        }
    }
}

void BattleVisitor::Visit(Pegasus& attacker, std::shared_ptr<NPC> defender) {
    // Пегасы никого не трогают — ничего не делаем
}

double BattleVisitor::Distance(const NPC& a, const NPC& b) const {
    double xx = a.GetX() - b.GetX();
    double yy = a.GetY() - b.GetY();
    return std::sqrt(xx * xx + yy * yy);
}

void BattleVisitor::Notify(const std::string& message) {
    for (auto& obs : observers) {
        obs->Notify(message);
    }
}