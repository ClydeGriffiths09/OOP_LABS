#pragma once

#include "concepts.hpp"

#include <cmath>
#include <iostream>

namespace figure {
    
constexpr double EPS = 1e-9;

template<Scalar T>
class Point {
public:
    T x;
    T y;
    Point() = default;
    Point(T x, T y);
};

template<Scalar T>
bool operator==(const Point<T>& point1, const Point<T>& point2);

template<Scalar T>
bool operator!=(const Point<T>& point1, const Point<T>& point2);

template<Scalar T>
std::ostream& operator<<(std::ostream& os, const Point<T>& p);

template<Scalar T>
std::istream& operator>>(std::istream& is, Point<T>& p);

template<Scalar T>
double Distance(const Point<T>& point1, const Point<T>& point2);

}

#include "point.ipp"