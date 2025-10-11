#pragma once

#include <exception>
#include <string>

namespace exceptions {
    class ElevenException : public std::exception {
        std::string msg;
    public:
        ElevenException(const std::string& m) : msg(m) {}
        const char* what() const noexcept override { return msg.c_str(); }
    };

    class VectorIsEmptyException : std::exception {
    public:
        explicit VectorIsEmptyException(const std::string& text) : error_message_(text) {
        }

        const char* what() const noexcept override {
            return error_message_.data();
        }

    private:
        std::string_view error_message_;
    };
}

