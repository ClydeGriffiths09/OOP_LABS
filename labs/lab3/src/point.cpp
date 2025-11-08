#include "point.h"

namespace figure {
    
Point::Point(double x, double y): x(x), y(y) {}

bool operator==(const Point& point1, const Point& point2) {
    bool x = std::fabs(point1.x - point2.x) < EPS;
    bool y = std::fabs(point1.y - point2.y) < EPS;
    return x && y;
}

bool operator!=(const Point& point1, const Point& point2) {
    return !(point1 == point2);
}

std::ostream& operator<<(std::ostream& os, const Point& point) {
    os << point.x << " " << point.y;
    return os;
}

std::istream& operator>>(std::istream& is, Point& point) {
    is >> point.x >> point.y;
    return is;
}

double Distance(const Point& p1, const Point& p2) {
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
}