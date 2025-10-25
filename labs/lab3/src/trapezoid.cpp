#include "trapezoid.h"
#include "exceptions.h"

namespace figure {
    Trapezoid::Trapezoid(): Trapezoid(Point(0, 0), Point(1, 0), Point(0.8, 1), Point(0.2, 1)) {}

    Trapezoid::Trapezoid(Point p1, Point p2, Point p3, Point p4){
        points[0] = new Point(p1.x, p1.y);
        points[1] = new Point(p2.x, p2.y);
        points[2] = new Point(p3.x, p3.y);
        points[3] = new Point(p4.x, p4.y);

        if (!Validate(p1, p2, p3, p4)) {
            Clear();
            throw exceptions::InvalidPointsException("Invalid points to create a rectangle");
        }
    }

    Trapezoid::Trapezoid(const Trapezoid& other) {
        for (size_t i = 0; i < ANGLES; ++i) {
            if (other.points[i] != nullptr) {
                points[i] = new Point(*other.points[i]);
            } else {
                points[i] = nullptr; 
            }
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
            for (size_t i = 0; i < ANGLES; ++i) {
                delete points[i];
            }
            
            for (size_t i = 0; i < ANGLES; ++i) {
                if (other.points[i] != nullptr) {
                    points[i] = new Point(*other.points[i]);
                } else {
                    points[i] = nullptr;
                }
            }
        }
        return *this;
    }

    Trapezoid::Trapezoid(Trapezoid&& other) noexcept {
        for (size_t i = 0; i < ANGLES; ++i) {
            points[i] = other.points[i];
            other.points[i] = nullptr;
        }
    }

    Trapezoid& Trapezoid::operator=(Trapezoid&& other) noexcept {
        if (this != &other) {
            Clear();
            
            for (size_t i = 0; i < ANGLES; ++i) {
                points[i] = other.points[i];
                other.points[i] = nullptr;
            }
        }
        return *this;
    }

    Point Trapezoid::Center() const {
        double center_x = 0.0, center_y = 0.0;
        int count = 0;
        
        for (size_t i = 0; i < ANGLES; ++i) {
            if (points[i]) {
                center_x += points[i]->x;
                center_y += points[i]->y;
                count++;
            }
        }
        
        if (count == 0) return Point(0, 0);

        return Point(center_x / count, center_y / count);
    }

    double Trapezoid::Area() const {
        if (!points[0] || !points[1] || !points[2] || !points[3]) {
            throw exceptions::InvalidPointsException("Invalid points for area calculation");
        }
        
        double base1, base2;
        
        if (AreParallel(*points[0], *points[1], *points[2], *points[3])) {
            base1 = Distance(*points[0], *points[1]);
            base2 = Distance(*points[2], *points[3]);
        } else {
            base1 = Distance(*points[0], *points[3]);
            base2 = Distance(*points[1], *points[2]);
        }
        
        double height = CalculateHeight();
        
        return (base1 + base2) * height * 0.5;
    }

    double Trapezoid::CalculateHeight() const {
        if (AreParallel(*points[0], *points[1], *points[2], *points[3])) {
            return PointToLineDistance(*points[2], *points[0], *points[1]);
        } else { 
            return PointToLineDistance(*points[1], *points[0], *points[3]);
        }
    }

    double Trapezoid::PointToLineDistance(Point p, Point a, Point b) const {
        double numerator = std::abs((b.y - a.y) * p.x - (b.x - a.x) * p.y + b.x * a.y - b.y * a.x);
        double denominator = Distance(a, b);
        return numerator / denominator;
    }

    Trapezoid::operator double() const {
        return Area();
    }

    void Trapezoid::Clear() {
        for (size_t i = 0; i < ANGLES; ++i) {
            delete points[i];
            points[i] = nullptr;
        }
    }

    Trapezoid::~Trapezoid() {
        Clear();
    }

    bool operator==(const Trapezoid& lf, const Trapezoid& rf) {
        if (!lf.points[0] || !lf.points[3] || !rf.points[0] || !rf.points[3]) {
            return false;
        }
        
        bool same_width = std::fabs(
            std::fabs(lf.points[0]->x - lf.points[3]->x) - 
            std::fabs(rf.points[0]->x - rf.points[3]->x)
        ) < EPS;
        
        bool same_height = std::fabs(
            std::fabs(lf.points[0]->y - lf.points[3]->y) - 
            std::fabs(rf.points[0]->y - rf.points[3]->y)
        ) < EPS;
        
        return same_width && same_height;
    }

    bool operator!=(const Trapezoid& lf, const Trapezoid& rf) {
        return !(lf == rf);
    }

    std::ostream& operator<<(std::ostream& os, const Trapezoid& r) {
        for (size_t i = 0; i < 4; ++i) {
            if (!r.points[i]) {
                os << "0 0";
            } else {
                os << r.points[i]->x << " " << r.points[i]->y;
            }
            
            if (i < 3) os << " ";
        }
        return os;
    }

    std::istream& operator>>(std::istream& is, Trapezoid& r) {
        Point ipoints[4];
        for (size_t i = 0; i < 4; ++i) {
            is >> ipoints[i];
        }
        
        Trapezoid temp(ipoints[0], ipoints[1], ipoints[2], ipoints[3]);
        std::swap(r.points, temp.points);
        
        return is;
    }
}