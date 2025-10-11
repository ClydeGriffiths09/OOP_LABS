#include "eleven.h"


namespace eleven {
    void Eleven::Normalize() {
        size_t lastNonZero = 0;
        for (size_t i = array_.Size(); i > 0; --i) {
            if (array_[i - 1] != 0) {
                lastNonZero = i;
                break;
            }
        }
        
        while (array_.Size() > lastNonZero) {
            array_.PopBack();
        }
        
        if (array_.Size() == 0) {
            array_.PushBack(0);
        }
    }

    Eleven::Eleven(): array_(vector::Vector())  {};

    Eleven::Eleven(const size_t& n, unsigned char c): array_(vector::Vector(n, c)) {};

    Eleven::Eleven(const std::initializer_list<unsigned char>& init) : array_(vector::Vector(init.size(), 0)) {
        size_t i = 0;
        for (unsigned char digit : init) {
            if (digit > 10) {
                throw exceptions::ElevenException("Digit must be between 0 and 10");
            }
            array_[i++] = digit;
        }
        if (array_.Size() == 0) {
            array_.PushBack(0);
        }
        Normalize();
    }

    Eleven::Eleven(const std::string& s): array_(vector::Vector(s.length(), 0)) {
        if (s.empty()) {
            array_.PushBack(0);
            return;
        }

        for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i) {
            char c = std::toupper(static_cast<unsigned char>(s[i]));
            unsigned char digit;
            if (c >= '0' && c <= '9') {
                digit = c - '0';
            } else if (c == 'A') {
                digit = 10;
            } else {
                throw exceptions::ElevenException("Invalid character in eleven-base number");
            }
            array_.PushBack(digit);
        }

        Normalize();
    };

    Eleven::Eleven(const Eleven& other) noexcept: array_(other.array_) {};

    Eleven::Eleven(Eleven&& other): array_(std::move(other.array_)) {};
        
    Eleven::~Eleven() noexcept {
        array_.Clear();
    };

    void Eleven::Copy(const Eleven& other) {
        array_.Copy(other.array_);
    };

    bool Eleven::GreaterThan(const Eleven& other) const {
        auto self = *this;
        auto othr = other;
        self.Normalize();
        othr.Normalize();

        if (self.array_.Size() != othr.array_.Size()) {
            return self.array_.Size() > othr.array_.Size();
        }

        for (size_t i = self.array_.Size(); i > 0; --i) {
            size_t idx = i - 1;
            if (self.array_[idx] != othr.array_[idx]) {
                return self.array_[idx] > othr.array_[idx];
            }
        }
        return false;
    };

    bool Eleven::LessThan(const Eleven& other) const {
        return !GreaterThan(other) && !Equal(other);
    };

    bool Eleven::Equal(const Eleven& other) const {
        auto self = *this;
        auto othr = other;
        self.Normalize();
        othr.Normalize();

        if (self.array_.Size() != othr.array_.Size()) {
            return false;
        }
        for (size_t i = 0; i < self.array_.Size(); ++i) {
            if (self.array_[i] != othr.array_[i]) {
                return false;
            }
        }
        return true;
    };

    Eleven Eleven::Add(const Eleven& m1, const Eleven& m2) {
        Eleven result;
        result.array_.Clear();

        size_t maxSize = (m1.array_.Size() > m2.array_.Size()) ? m1.array_.Size() : m2.array_.Size();
        unsigned char carry = 0;

        for (size_t i = 0; i < maxSize || carry; ++i) {
            unsigned char d1 = (i < m1.array_.Size()) ? m1.array_[i] : 0;
            unsigned char d2 = (i < m2.array_.Size()) ? m2.array_[i] : 0;

            if (d1 > 10 || d2 > 10) {
                throw exceptions::ElevenException("Invalid digit in number");
            }

            unsigned int sum = static_cast<unsigned int>(d1) + static_cast<unsigned int>(d2) + carry;
            carry = static_cast<unsigned char>(sum / 11);
            unsigned char digit = static_cast<unsigned char>(sum % 11);

            result.array_.PushBack(digit);
        }

        result.Normalize();
        return result;
    }

    Eleven Eleven::Sub(const Eleven& m1, const Eleven& m2) {
        if (m1.LessThan(m2)) {
            throw exceptions::ElevenException("Subtraction result would be negative");
        }

        Eleven result;
        result.array_.Clear();

        unsigned char borrow = 0;
        for (size_t i = 0; i < m1.array_.Size(); ++i) {
            unsigned char d1 = m1.array_[i];
            unsigned char d2 = (i < m2.array_.Size()) ? m2.array_[i] : 0;

            if (d1 > 10 || d2 > 10) {
                throw exceptions::ElevenException("Invalid digit in number");
            }

            int diff = static_cast<int>(d1) - static_cast<int>(d2) - borrow;
            if (diff < 0) {
                diff += 11;
                borrow = 1;
            } else {
                borrow = 0;
            }

            result.array_.PushBack(static_cast<unsigned char>(diff));
        }

        result.Normalize();
        return result;
    }

    std::string Eleven::ToString() const {
        if (array_.Size() == 0) {
            return "0";
        }
        
        std::string result;
        
        for (size_t i = 0; i < array_.Size(); ++i) {
            size_t idx = i;
            unsigned char digit = array_[idx];
            bool flag = true;
            if (digit == 0 && flag) {
                continue;
            } else if (digit < 10) {
                result += static_cast<char>('0' + digit);
                flag = false;
            } else if (digit == 10) {
                result += 'A';
                flag = false;
            } else {
                throw exceptions::ElevenException("Invalid digit in conversion to string");
            }
        }

        std::string s;
        for (int i = result.length() - 1; i >= 0; --i) {
            s += result[i];
        }

        if (s == "") {
            return "0";
        }
        return s;
    }
}
