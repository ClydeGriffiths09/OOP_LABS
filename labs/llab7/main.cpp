#include <iostream>
#include "dungeon_editor.hpp"
#include "simulation.hpp"

int main() {
    std::cout << "=== Balagur Fate 3 ===\n";
    std::cout << "1. Dungeon Editor (original lab)\n";
    std::cout << "2. NPC Simulation (30-second battle)\n";
    std::cout << "0. Exit\n> ";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        DungeonEditor editor;
        editor.Run();
    } else if (choice == 2) {
        Simulation sim;
        sim.run();
    } else {
        std::cout << "Goodbye!\n";
    }

    return 0;
}