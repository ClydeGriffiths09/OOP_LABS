#pragma once

#include "point.hpp"

#include <iostream>
#include <memory>

namespace figure {

const int16_t SQUARE_ANGLES = 4;
const int16_t RECTANGLE_ANGLES = 4;
const int16_t TRIANGLE_ANGLES = 3;

template<Scalar T>
class Figure {
public:
    virtual Point<T> Center() const = 0;
    virtual double Area() const = 0;
    virtual explicit operator double() const = 0;
    virtual ~Figure() = default;
};

template<Scalar T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& fig);

template<Scalar T>
std::istream& operator>>(std::istream& is, Figure<T>& fig);

}