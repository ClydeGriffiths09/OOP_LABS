#include "square.hpp"
#include "exceptions.hpp"

namespace figure {

template<Scalar T>
Square<T>::Square() {
    points = std::make_unique<Point<T>[]>(SQUARE_ANGLES);
    points[0] = Point<T>(0, 0);
    points[1] = Point<T>(1, 0);
    points[2] = Point<T>(1, 1);
    points[3] = Point<T>(0, 1);
}

template<Scalar T>
Square<T>::Square(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4){
    if (!Validate(p1, p2, p3, p4)) {
        throw exceptions::InvalidPointsException("Invalid points to create a Square");
    }

    points = std::make_unique<Point<T>[]>(SQUARE_ANGLES);
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    points[3] = p4;
}

template<Scalar T>
Square<T>::Square(const Square<T>& other) {
    points = std::make_unique<Point<T>[]>(SQUARE_ANGLES);
    for (size_t i = 0; i < SQUARE_ANGLES; ++i) {
        points[i] = other.points[i];
    }
}

template<Scalar T>
bool Square<T>::Validate(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4) const {
    double side1 = Distance(p1, p2);
    double side2 = Distance(p2, p3);
    double side3 = Distance(p3, p4);
    double side4 = Distance(p4, p1);
    
    bool equal_sides = std::abs(side1 - side2) < EPS &&
                       std::abs(side2 - side3) < EPS &&
                       std::abs(side3 - side4) < EPS;
    
    T dx1 = p2.x - p1.x, dy1 = p2.y - p1.y;
    T dx2 = p3.x - p2.x, dy2 = p3.y - p2.y;
    
    bool right_angle = std::abs(dx1 * dx2 + dy1 * dy2) < EPS;
    
    return equal_sides && right_angle;
}

template<Scalar T>
Square<T>& Square<T>::operator=(const Square<T>& other) {
    if (this != &other) {
        points = std::make_unique<Point<T>[]>(SQUARE_ANGLES);
        for (size_t i = 0; i < SQUARE_ANGLES; ++i) {
            points[i] = other.points[i];
        }
    }
    return *this;
}

template<Scalar T>
Square<T>::Square(Square<T>&& other) noexcept 
    : points(std::move(other.points)) {
}

template<Scalar T>
Square<T>& Square<T>::operator=(Square<T>&& other) noexcept {
    if (this != &other) {
        points = std::move(other.points);
    }
    return *this;
}

template<Scalar T>
Point<T> Square<T>::Center() const {
    T center_x = (points[0].x + points[1].x + points[2].x + points[3].x) / 4.0;
    T center_y = (points[0].y + points[1].y + points[2].y + points[3].y) / 4.0;
    
    return Point<T>(center_x, center_y);
}

template<Scalar T>
double Square<T>::Area() const {
    double side = Distance(points[0], points[1]);
    return side * side;
}

template<Scalar T>
Square<T>::operator double() const {
    return Area();
}

template<Scalar U>
bool operator==(const Square<U>& lf, const Square<U>& rf) {
    
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

template<Scalar U>
bool operator!=(const Square<U>& lf, const Square<U>& rf) {
    return !(lf == rf);
}

template<Scalar U>
std::ostream& operator<<(std::ostream& os, const Square<U>& r) {
    for (size_t i = 0; i < SQUARE_ANGLES; ++i) {
        os << r.points[i].x << " " << r.points[i].y;
        if (i < 3) os << " ";
    }
    return os;
}

template<Scalar U>
std::istream& operator>>(std::istream& is, Square<U>& r) {
    Point<U> points[SQUARE_ANGLES];
    for (size_t i = 0; i < SQUARE_ANGLES; ++i) {
        is >> points[i];
    }
    
    Square<U> temp(points[0], points[1], points[2], points[3]);
    r = std::move(temp);
    
    return is;
}
}