#include "simulation.hpp"
#include "npc_factory.hpp"
#include "battle_visitor.hpp"
#include <iostream>
#include <random>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <sstream>

void Simulation::movementThread() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> move_dist(-1.0, 1.0);

    while (state.running) {
        {
            std::unique_lock<std::shared_mutex> lock(state.npc_mutex);
            for (auto& npc : state.npcs) {
                if (!npc->IsAlive()) continue;
                double dx = move_dist(gen);
                double dy = move_dist(gen);
                npc->Move(dx, dy, state.MAP_SIZE);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void Simulation::battleThread() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> die(1, 6);

    while (state.running) {
        std::vector<std::pair<std::shared_ptr<NPC>, std::shared_ptr<NPC>>> pairs;

        {
            std::shared_lock<std::shared_mutex> lock(state.npc_mutex);
            const auto& npcs = state.npcs;
            for (size_t i = 0; i < npcs.size(); ++i) {
                if (!npcs[i]->IsAlive()) continue;
                for (size_t j = i + 1; j < npcs.size(); ++j) {
                    if (!npcs[j]->IsAlive()) continue;
                    if (BattleSystem::Distance(*npcs[i], *npcs[j]) <= BATTLE_RANGE) {
                        pairs.emplace_back(npcs[i], npcs[j]);
                    }
                }
            }
        }

        for (auto& [a, b] : pairs) {
            if (!a->IsAlive() || !b->IsAlive()) continue;

            int attack = die(gen);
            int defense = die(gen);

            auto logBattle = [&](const std::string& msg) {
                std::lock_guard<std::mutex> lock(state.cout_mutex);
                std::cout << "[BATTLE] " << msg << "\n";
            };

            if (attack > defense) {
                b->Kill();
                logBattle(a->GetName() + " (" + a->GetType() + ") killed " +
                          b->GetName() + " (" + b->GetType() + ")");
            } else if (defense > attack) {
                a->Kill();
                logBattle(b->GetName() + " (" + b->GetType() + ") killed " +
                          a->GetName() + " (" + a->GetType() + ")");
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

void Simulation::renderThread() {
    for (int sec = 0; sec < SIMULATION_TIME_SEC; ++sec) {
        std::cout << "\033[2J\033[1;1H";

        std::vector<std::string> map(30, std::string(30, '.'));

        {
            std::shared_lock<std::shared_mutex> lock(state.npc_mutex);
            for (const auto& npc : state.npcs) {
                if (npc->IsAlive()) {
                    int x = static_cast<int>(std::round(npc->GetX()));
                    int y = static_cast<int>(std::round(npc->GetY()));
                    if (x >= 0 && x < 30 && y >= 0 && y < 30) {
                        char symbol = '?';
                        if (npc->GetType() == "Knight") symbol = 'K';
                        else if (npc->GetType() == "Squirrel") symbol = 'S';
                        else if (npc->GetType() == "Pegasus") symbol = 'P';
                        map[y][x] = symbol;
                    }
                }
            }
        }

        {
            std::lock_guard<std::mutex> lock(state.cout_mutex);
            std::cout << "=== Second " << (sec + 1) << " / " << SIMULATION_TIME_SEC << " ===\n";
            for (int i = 0; i < 30; ++i) {
                std::cout << map[i] << "\n";
            }
            std::cout << "\n";
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    state.running = false;
}

void Simulation::run() {
    constexpr int NPC_COUNT = 50;
    std::vector<std::string> types = {"Knight", "Squirrel", "Pegasus"};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> coord(0.0, state.MAP_SIZE - 1.0);
    std::uniform_int_distribution<> type_dist(0, 2);

    for (int i = 0; i < NPC_COUNT; ++i) {
        double x = coord(gen), y = coord(gen);
        std::string type = types[type_dist(gen)];
        std::string name = type + "_" + std::to_string(i);
        state.npcs.push_back(NPCFactory::CreateNPC(type, x, y, name));
    }

    std::cout << "\nStarting NPC Simulation (30х30 map, 50 NPCs, 30 seconds)...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::thread mover(&Simulation::movementThread, this);
    std::thread fighter(&Simulation::battleThread, this);
    std::thread renderer(&Simulation::renderThread, this);

    renderer.join();
    mover.join();
    fighter.join();

    // Вывод выживших
    {
        std::lock_guard<std::mutex> lock(state.cout_mutex);
        std::cout << "\n" << std::string(60, '=') << "\n";
        std::cout << "FINAL SURVIVORS:\n";
        int count = 0;
        for (const auto& npc : state.npcs) {
            if (npc->IsAlive()) {
                std::cout << "  " << std::setw(10) << npc->GetType()
                          << " " << std::setw(12) << npc->GetName()
                          << " at (" << std::fixed << std::setprecision(1)
                          << npc->GetX() << ", " << npc->GetY() << ")\n";
                count++;
            }
        }
        std::cout << "\nTotal survivors: " << count << " / " << NPC_COUNT << "\n";
        std::cout << std::string(60, '=') << "\n";
    }
}