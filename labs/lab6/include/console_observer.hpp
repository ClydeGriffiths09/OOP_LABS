#pragma once

#include <iostream>

#include "observer.hpp"

class ConsoleObserver: public Observer {
public:
    void Notify(const std::string& message) override;
};