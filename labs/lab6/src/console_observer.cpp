#include <iostream>

#include "console_observer.hpp"

void ConsoleObserver::Notify(const std::string& message) {
    std::cout << "[CONSOLE] " << message << std::endl;
}