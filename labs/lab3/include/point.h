#pragma once

#include <cmath>
#include <iostream>

namespace figure {
    
constexpr double EPS = 1e-9;

class Point {
public:
    double x;
    double y;
    Point() = default;
    Point(double x, double y);
};

bool operator==(const Point& point1, const Point& point2);
bool operator!=(const Point& point1, const Point& point2);
std::ostream& operator<<(std::ostream& os, const Point& p);
std::istream& operator>>(std::istream& is, Point& p);

double Distance(const Point& point1, const Point& point2);
}