#pragma once 

#include <initializer_list>
#include <iostream>
#include <string>

#include "vector.h"
#include "exceptions.h"

namespace eleven {
class Eleven {  
private:
    vector::Vector array_;

    void Normalize();

public:
    Eleven();

    Eleven(const size_t& n, unsigned char c = 0);

    Eleven(const std::initializer_list<unsigned char>& init);

    Eleven(const std::string& s);

    Eleven(const Eleven& other) noexcept;

    Eleven(Eleven&& other);
    
    ~Eleven() noexcept;

    void Copy(const Eleven& other);

    bool GreaterThan(const Eleven& other) const;

    bool LessThan(const Eleven& other) const;

    bool Equal(const Eleven& other) const;

    static Eleven Add(const Eleven& m1, const Eleven& m2);

    static Eleven Sub(const Eleven& m1, const Eleven& m2);

    std::string ToString() const;
};

}