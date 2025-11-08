#pragma once

#include "point.h"

#include <iostream>

namespace figure {

const int16_t TRAPEZOIDANGLES = 4;
const int16_t RECTANGLEANGLES = 4;
const int16_t RHOMBUSANGLES = 4;

class Figure {
public:
    virtual Point Center() const = 0;
    virtual double Area() const = 0;
    virtual operator double() const = 0;
    virtual ~Figure() = default;
};

std::ostream& operator<<(std::ostream& os, const Figure& fig);
std::istream& operator>>(std::istream& is, Figure& fig);
}