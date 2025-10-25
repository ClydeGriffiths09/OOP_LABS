#include "rhombus.h"
#include "exceptions.h"

namespace figure {
    Rhombus::Rhombus(): Rhombus(Point(0, 0), Point(0.5, 0.866), Point(1, 0), Point(0.5, -0.866)) {}

    Rhombus::Rhombus(Point p1, Point p2, Point p3, Point p4){
        points[0] = new Point(p1.x, p1.y);
        points[1] = new Point(p2.x, p2.y);
        points[2] = new Point(p3.x, p3.y);
        points[3] = new Point(p4.x, p4.y);

        if (!Validate(p1, p2, p3, p4)) {
            Clear();
            throw exceptions::InvalidPointsException("Invalid points to create a rectangle");
        }
    }

    Rhombus::Rhombus(const Rhombus& other) {
        for (size_t i = 0; i < ANGLES; ++i) {
            if (other.points[i] != nullptr) {
                points[i] = new Point(*other.points[i]);
            } else {
                points[i] = nullptr; 
            }
        }
    }

    bool Rhombus::Validate(Point p1, Point p2, Point p3, Point p4) const {
        // All points are not equal
        if (p1 == p2 || p1 == p3 || p1 == p4 || 
            p2 == p3 || p2 == p4 || p3 == p4) {
            return false;
        }

        // All sides are equal
        double side1_sq = (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
        double side2_sq = (p3.x - p2.x) * (p3.x - p2.x) + (p3.y - p2.y) * (p3.y - p2.y);
        double side3_sq = (p4.x - p3.x) * (p4.x - p3.x) + (p4.y - p3.y) * (p4.y - p3.y);
        double side4_sq = (p1.x - p4.x) * (p1.x - p4.x) + (p1.y - p4.y) * (p1.y - p4.y);

        if (std::fabs(side1_sq - side2_sq) > EPS ||
            std::fabs(side1_sq - side3_sq) > EPS ||
            std::fabs(side1_sq - side4_sq) > EPS) {
            return false;
        }

        return true;
    }

    Rhombus& Rhombus::operator=(const Rhombus& other) {
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

    Rhombus::Rhombus(Rhombus&& other) noexcept {
        for (size_t i = 0; i < ANGLES; ++i) {
            points[i] = other.points[i];
            other.points[i] = nullptr;
        }
    }

    Rhombus& Rhombus::operator=(Rhombus&& other) noexcept {
        if (this != &other) {
            Clear();
            
            for (size_t i = 0; i < ANGLES; ++i) {
                points[i] = other.points[i];
                other.points[i] = nullptr;
            }
        }
        return *this;
    }

    Point Rhombus::Center() const {
        double center_x = 0.0, center_y = 0.0;
        int count = 0;
        
        for (size_t i = 0; i < ANGLES; ++i) {
            if (points[i]) {
                center_x += points[i]->x;
                center_y += points[i]->y;
                count++;
            }
        }
        
        if (count == 0) {
            return Point(0, 0);
        }

        return Point(center_x / count, center_y / count);
    }

    double Rhombus::Area() const {
        if (!points[0] || !points[1] || !points[2] || !points[3]) {
            throw exceptions::InvalidPointsException("Invalid points for area calculation");
        }
        
        // 1 Diagonal length (p1-p3)
        double diag1 = std::sqrt(
            (points[2]->x - points[0]->x) * (points[2]->x - points[0]->x) + 
            (points[2]->y - points[0]->y) * (points[2]->y - points[0]->y)
        );
        
        // 2 Diagonal length (p2-p4)  
        double diag2 = std::sqrt(
            (points[3]->x - points[1]->x) * (points[3]->x - points[1]->x) + 
            (points[3]->y - points[1]->y) * (points[3]->y - points[1]->y)
        );
        
        return (diag1 * diag2) * 0.5;
    }

    Rhombus::operator double() const {
        return Area();
    }

    void Rhombus::Clear() {
        for (size_t i = 0; i < ANGLES; ++i) {
            delete points[i];
            points[i] = nullptr;
        }
    }

    Rhombus::~Rhombus() {
        Clear();
    }

    bool operator==(const Rhombus& lf, const Rhombus& rf) {
        for (size_t i = 0; i < 4; ++i) {
            if (!lf.points[i] != !rf.points[i]) {
                return false;
            }

            if (lf.points[i] && rf.points[i] && *lf.points[i] != *rf.points[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Rhombus& lf, const Rhombus& rf) {
        return !(lf == rf);
    }

    std::ostream& operator<<(std::ostream& os, const Rhombus& r) {
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

    std::istream& operator>>(std::istream& is, Rhombus& r) {
        Point ipoints[4];
        for (size_t i = 0; i < 4; ++i) {
            is >> ipoints[i];
        }
        
        Rhombus temp(ipoints[0], ipoints[1], ipoints[2], ipoints[3]);
        std::swap(r.points, temp.points);
        
        return is;
    }
}