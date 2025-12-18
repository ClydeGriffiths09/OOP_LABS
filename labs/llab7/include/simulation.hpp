#pragma once

#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include "npc.hpp"

class Simulation {
private:
    struct State {
        std::vector<std::shared_ptr<NPC>> npcs;
        mutable std::shared_mutex npc_mutex;
        std::mutex cout_mutex;
        bool running = true;
        static constexpr double MAP_SIZE = 30.0;
    };

    State state;
    constexpr static int SIMULATION_TIME_SEC = 30;
    constexpr static double BATTLE_RANGE = 5.0;

    void movementThread();
    void battleThread();
    void renderThread();

public:
    void run();
};