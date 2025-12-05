#include <iostream>
#include <limits>
#include <vector>
#include <memory>

#include "dungeon_editor.hpp"
#include "npc_factory.hpp"

void DungeonEditor::Run() {
    std::cout << "=== Balagur Fate 3 Dungeon Editor ===\n";

    while (true) {
        std::cout << "\n1. Add NPC\n2. Print NPCs\n3. Save to file\n4. Load from file\n5. Battle mode\n0. Exit\n> ";
        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 0) {
            break;
        }

        switch (choice) {
            case 1: {
                std::cout << "Type (Knight/Squirrel/Pegasus): ";
                std::string type;
                std::cin >> type;

                std::cout << "Name: ";
                std::string name;
                std::cin.ignore();
                std::getline(std::cin, name);

                double x, y;
                std::cout << "X (0-500): ";
                std::cin >> x;
                std::cout << "Y (0-500): ";
                std::cin >> y;

                try {
                    auto npc = NPCFactory::CreateNPC(type, x, y, name);
                    handler.AddNPC(npc);
                    std::cout << "Added " << type << " '" << name << "'\n";
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 2:
                handler.PrintAll();
                break;
            case 3: {
                std::cout << "Filename: ";
                std::string fname;
                std::cin >> fname;
                handler.SaveToFile(fname);
                break;
            }
            case 4: {
                std::cout << "Filename: ";
                std::string fname;
                std::cin >> fname;
                handler.LoadFromFile(fname);
                break;
            }
            case 5: {
                double range;
                std::cout << "Battle range: ";
                std::cin >> range;

                if (range < 0) {
                    std::cout << "Range must be non-negative!\n";
                    break;
                }

                BattleSystem visitor(range);
                visitor.AddObserver(std::make_shared<ConsoleObserver>());
                visitor.AddObserver(std::make_shared<FileObserver>());

                const auto& npcs = handler.GetNPCs();
                if (npcs.empty()) {
                    std::cout << "No NPCs to fight!\n";
                    break;
                }

                std::vector<bool> alive(npcs.size(), true);
                size_t count = npcs.size();

                for (size_t i = 0; i < count; ++i) {
                    if (!alive[i]) continue;
                    for (size_t j = 0; j < count; ++j) {
                        if (i == j || !alive[j]) continue;
                        npcs[i]->Accept(visitor, npcs[j]);
                        if (npcs[i]->Fight(npcs[j])) {
                            alive[j] = false;
                        }
                    }
                }

                std::vector<std::shared_ptr<NPC>> survivors;
                for (size_t i = 0; i < count; ++i) {
                    if (alive[i]) {
                        survivors.push_back(npcs[i]);
                    }
                }
                const_cast<std::vector<std::shared_ptr<NPC>>&>(npcs) = std::move(survivors);

                std::cout << "Battle finished. Survivors: " << handler.GetNPCs().size() << "\n";
                break;
            }
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}