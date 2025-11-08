#include "trapezoid.h"
#include "exceptions.h"

namespace figure {

Trapezoid::Trapezoid(): Trapezoid(Point(0, 0), Point(1, 0), Point(0.8, 1), Point(0.2, 1)) {}

Trapezoid::Trapezoid(Point p1, Point p2, Point p3, Point p4){
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    points[3] = p4;

    if (!Validate(p1, p2, p3, p4)) {
        throw exceptions::InvalidPointsException("Invalid points to create a rectangle");
    }
}

Trapezoid::Trapezoid(const Trapezoid& other) {
    for (size_t i = 0; i < TRAPEZOIDANGLES; ++i) {
        points[i] = other.points[i];
    }
}

bool Trapezoid::Validate(Point p1, Point p2, Point p3, Point p4) const {
    // All points are not equal
    if (p1 == p2 || p1 == p3 || p1 == p4 || 
        p2 == p3 || p2 == p4 || p3 == p4) {
        return false;
    }

    // AB  CD
    bool ab_cd_parallel = AreParallel(p1, p2, p3, p4);
    // BC  AD  
    bool bc_ad_parallel = AreParallel(p2, p3, p4, p1);

    return (ab_cd_parallel && !bc_ad_parallel) || (!ab_cd_parallel && bc_ad_parallel);
}

bool Trapezoid::AreParallel(Point a, Point b, Point c, Point d) const {
    double vec1_x = b.x - a.x, vec1_y = b.y - a.y;
    double vec2_x = d.x - c.x, vec2_y = d.y - c.y;
    
    return std::fabs(vec1_x * vec2_y - vec1_y * vec2_x) <= EPS;
}

Trapezoid& Trapezoid::operator=(const Trapezoid& other) {
    if (this != &other) {
        for (size_t i = 0; i < TRAPEZOIDANGLES; ++i) {
            points[i] = other.points[i];
        }
    }
    return *this;
}

Trapezoid::Trapezoid(Trapezoid&& other) noexcept {
    for (size_t i = 0; i < TRAPEZOIDANGLES; ++i) {
        points[i] = std::move(other.points[i]);
    }
}

Trapezoid& Trapezoid::operator=(Trapezoid&& other) noexcept {
    if (this != &other) {
        for (size_t i = 0; i < TRAPEZOIDANGLES; ++i) {
            points[i] = std::move(other.points[i]);
        }
    }
    return *this;
}

Point Trapezoid::Center() const {
    double center_x = 0.0, center_y = 0.0;
    int count = 0;
    
    for (size_t i = 0; i < TRAPEZOIDANGLES; ++i) {
        center_x += points[i].x;
        center_y += points[i].y;
        count++;
    }
    
    if (count == 0) return Point(0, 0);

    return Point(center_x / count, center_y / count);
}

double Trapezoid::Area() const {   
    double base1, base2;
    
    if (AreParallel(points[0], points[1], points[2], points[3])) {
        base1 = Distance(points[0], points[1]);
        base2 = Distance(points[2], points[3]);
    } else {
        base1 = Distance(points[0], points[3]);
        base2 = Distance(points[1], points[2]);
    }
    
    double height = CalculateHeight();
    
    return (base1 + base2) * height * 0.5;
}

double Trapezoid::CalculateHeight() const {
    if (AreParallel(points[0], points[1], points[2], points[3])) {
        return PointToLineDistance(points[2], points[0], points[1]);
    } else { 
        return PointToLineDistance(points[1], points[0], points[3]);
    }
}

double Trapezoid::PointToLineDistance(Point p, Point a, Point b) {
    double numerator = std::abs((b.y - a.y) * p.x - (b.x - a.x) * p.y + b.x * a.y - b.y * a.x);
    double denominator = Distance(a, b);
    return numerator / denominator;
}

Trapezoid::operator double() const {
    return Area();
}

bool operator==(const Trapezoid& lf, const Trapezoid& rf) {
    bool same_width = std::fabs(
        std::fabs(lf.points[0].x - lf.points[3].x) - 
        std::fabs(rf.points[0].x - rf.points[3].x)
    ) < EPS;
    
    bool same_height = std::fabs(
        std::fabs(lf.points[0].y - lf.points[3].y) - 
        std::fabs(rf.points[0].y - rf.points[3].y)
    ) < EPS;
    
    return same_width && same_height;
}

bool operator!=(const Trapezoid& lf, const Trapezoid& rf) {
    return !(lf == rf);
}

std::ostream& operator<<(std::ostream& os, const Trapezoid& r) {
    for (size_t i = 0; i < TRAPEZOIDANGLES; ++i) {
        os << r.points[i].x << " " << r.points[i].y;
        if (i < 3) os << " ";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Trapezoid& r) {
    Point ipoints[TRAPEZOIDANGLES];
    for (size_t i = 0; i < TRAPEZOIDANGLES; ++i) {
        is >> ipoints[i];
    }
    
    r = Trapezoid(ipoints[0], ipoints[1], ipoints[2], ipoints[3]);
    
    return is;
}
}