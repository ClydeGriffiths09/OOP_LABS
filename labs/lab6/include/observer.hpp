#pragma once

#include <string>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void Notify(const std::string& message) = 0;
};