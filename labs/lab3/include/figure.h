#pragma once

#include <algorithm> 
#include <vector>
#include <initializer_list>
#include "point.h"

namespace figure {
    constexpr int16_t ANGLES = 4;

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