#include <cmath>
#include <sstream>
#include <memory>
#include <random>
#include "battle_visitor.hpp"
#include "npc.hpp"

// Генератор для кубиков (используется ТОЛЬКО в симуляции, но оставим здесь)
static std::mt19937 gen(std::random_device{}());
static std::uniform_int_distribution<> die(1, 6);

BattleSystem::BattleSystem(double range) : range(range) {}

void BattleSystem::AddObserver(std::shared_ptr<Observer> obs) {
    observers.push_back(std::move(obs));
}

// === РЕЖИМ РЕДАКТОРА: ДЕТЕРМИНИРОВАННЫЙ БОЙ ===
// (используется в DungeonEditor при выборе "Battle mode")
void BattleSystem::Visit(Knight& attacker, std::shared_ptr<NPC> defender) {
    if (Distance(attacker, *defender) <= range) {
        if (attacker.Fight(defender)) {
            std::ostringstream oss;
            oss << attacker.GetName() << " (Knight) killed " 
                << defender->GetName() << " (" << defender->GetType() << ")";
            Notify(oss.str()); 
        }
    }
}

void BattleSystem::Visit(Squirrel& attacker, std::shared_ptr<NPC> defender) {
    if (Distance(attacker, *defender) <= range) {
        if (attacker.Fight(defender)) {
            std::ostringstream oss;
            oss << attacker.GetName() << " (Squirrel) killed " 
                << defender->GetName() << " (" << defender->GetType() << ")";
            Notify(oss.str()); 
        }
    }
}

void BattleSystem::Visit(Pegasus& attacker, std::shared_ptr<NPC> defender) {
    // Пегасы никого не трогают
}

// === ОБЩИЙ МЕТОД РАССТОЯНИЯ ===
double BattleSystem::Distance(const NPC& a, const NPC& b) {
    double dx = a.GetX() - b.GetX();
    double dy = a.GetY() - b.GetY();
    return std::sqrt(dx * dx + dy * dy);
}

void BattleSystem::Notify(const std::string& message) {
    for (auto& obs : observers) {
        obs->Notify(message);
    }
}