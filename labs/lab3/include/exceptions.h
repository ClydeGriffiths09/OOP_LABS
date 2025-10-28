#pragma once

#include <stdexcept>
#include <string>

namespace exceptions {

class InvalidPointsException: std::runtime_error {
public:
    explicit InvalidPointsException(const std::string& text): std::runtime_error(text) {}
};

class InvalidIndex : std::runtime_error {
public:
  explicit InvalidIndex(const std::string &text) : std::runtime_error(text) {}
};

class VectorIsNull : std::runtime_error {
public:
  explicit VectorIsNull(const std::string &text) : std::runtime_error(text) {}
};
}