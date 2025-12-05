#pragma once

#include "point.hpp"

namespace figure {

template<Scalar T>
Point<T>::Point(T x, T y): x(x), y(y) {}

template<Scalar T>
bool operator==(const Point<T>& point1, const Point<T>& point2) {
    bool x = std::fabs(point1.x - point2.x) < EPS;
    bool y = std::fabs(point1.y - point2.y) < EPS;
    return x && y;
}

template<Scalar T>
bool operator!=(const Point<T>& point1, const Point<T>& point2) {
    return !(point1 == point2);
}

template<Scalar T>
std::ostream& operator<<(std::ostream& os, const Point<T>& point) {
    os << point.x << " " << point.y;
    return os;
}

template<Scalar T>
std::istream& operator>>(std::istream& is, Point<T>& point) {
    is >> point.x >> point.y;
    return is;
}

template<Scalar T>
double Distance(const Point<T>& p1, const Point<T>& p2) {
    T dx = p1.x - p2.x;
    T dy = p1.y - p2.y;
    return std::sqrt(dx * dx + dy * dy);
}

}