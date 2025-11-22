#pragma once

#include <stdexcept>
#include <string>

namespace exceptions {

class InvalidIndex : public std::runtime_error {
public:
    explicit InvalidIndex(const std::string& text) : std::runtime_error(text) {}
};

class VectorIsNull : public std::runtime_error {
public:
    explicit VectorIsNull(const std::string& text) : std::runtime_error(text) {}
};

}