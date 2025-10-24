#include "rectangle.h"
#include "exceptions.h"

namespace figure {
    Rectangle::Rectangle(): Rectangle(Point(0, 0), Point(0, 1), Point(1, 1), Point(1, 0)) {}

    Rectangle::Rectangle(Point p1, Point p2, Point p3, Point p4){
        points[0] = new Point(p1.x, p1.y);
        points[1] = new Point(p2.x, p2.y);
        points[2] = new Point(p3.x, p3.y);
        points[3] = new Point(p4.x, p4.y);

        if (!Validate(p1, p2, p3, p4)) {
            Clear();
            throw exceptions::InvalidPointsException("Invalid points to create a rectangle");
        }
    }

    Rectangle::Rectangle(const Rectangle& other) {
        for (size_t i = 0; i < ANGLES; ++i) {
            if (other.points[i] != nullptr) {
                points[i] = new Point(*other.points[i]);
            } else {
                points[i] = nullptr; 
            }
        }
    }

    bool Rectangle::Validate(Point p1, Point p2, Point p3, Point p4) const {
        // All points are not equal
        if (p1 == p2 || p1 == p3 || p1 == p4 || 
            p2 == p3 || p2 == p4 || p3 == p4) {
            return false;
        }

        // Centers of diagonals are equal
        Point center1{(p1.x + p3.x) * 0.5, (p1.y + p3.y) * 0.5};
        Point center2{(p2.x + p4.x) * 0.5, (p2.y + p4.y) * 0.5};
        
        if (std::fabs(center1.x - center2.x) > EPS || 
            std::fabs(center1.y - center2.y) > EPS) {
            return false;
        }

        // Diagonals are equal
        double diag1_sq = (p1.x - p3.x) * (p1.x - p3.x) + (p1.y - p3.y) * (p1.y - p3.y);
        double diag2_sq = (p2.x - p4.x) * (p2.x - p4.x) + (p2.y - p4.y) * (p2.y - p4.y);

        return std::fabs(diag1_sq - diag2_sq) <= EPS;
    }

    Rectangle& Rectangle::operator=(const Rectangle& other) {
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

    Rectangle::Rectangle(Rectangle&& other) noexcept {
        for (size_t i = 0; i < ANGLES; ++i) {
            points[i] = other.points[i];
            other.points[i] = nullptr;
        }
    }

    Rectangle& Rectangle::operator=(Rectangle&& other) noexcept {
        if (this != &other) {
            Clear();
            
            for (size_t i = 0; i < ANGLES; ++i) {
                points[i] = other.points[i];
                other.points[i] = nullptr;
            }
        }
        return *this;
    }

    Point Rectangle::Center() const {
        double center_x = (points[0]->x + points[1]->x + points[2]->x + points[3]->x) / 4.0;
        double center_y = (points[0]->y + points[1]->y + points[2]->y + points[3]->y) / 4.0;
        
        return Point(center_x, center_y);
    }

    double Rectangle::Area() const {
        if (!points[0] || !points[2]) {
            throw exceptions::InvalidPointsException("Invalid points");
        }
        
        double area = (std::fabs(points[0]->x - points[2]->x) * std::fabs(points[0]->y - points[2]->y));
        return area;
    }

    Rectangle::operator double() const {
        return Area();
    }

    void Rectangle::Clear() {
        for (size_t i = 0; i < ANGLES; ++i) {
            delete points[i];
            points[i] = nullptr;
        }
    }

    Rectangle::~Rectangle() {
        Clear();
    }

    bool operator==(const Rectangle& lf, const Rectangle& rf) {
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

    bool operator!=(const Rectangle& lf, const Rectangle& rf) {
        return !(lf == rf);
    }

    std::ostream& operator<<(std::ostream& os, const Rectangle& r) {
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

    std::istream& operator>>(std::istream& is, Rectangle& r) {
        Point ipoints[4];
        for (size_t i = 0; i < 4; ++i) {
            is >> ipoints[i];
        }
        
        Rectangle temp(ipoints[0], ipoints[1], ipoints[2], ipoints[3]);
        std::swap(r.points, temp.points);
        
        return is;
    }
}
