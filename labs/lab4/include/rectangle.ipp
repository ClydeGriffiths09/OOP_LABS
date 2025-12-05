#include "rectangle.hpp"
#include "exceptions.hpp"

namespace figure {

template<Scalar T>
Rectangle<T>::Rectangle() {
    points = std::make_unique<Point<T>[]>(RECTANGLE_ANGLES);
    points[0] = Point<T>(0, 0);
    points[1] = Point<T>(1, 0);
    points[2] = Point<T>(1, 1);
    points[3] = Point<T>(0, 1);
}

template<Scalar T>
Rectangle<T>::Rectangle(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4){
    if (!Validate(p1, p2, p3, p4)) {
        throw exceptions::InvalidPointsException("Invalid points to create a rectangle");
    }

    points = std::make_unique<Point<T>[]>(RECTANGLE_ANGLES);
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    points[3] = p4;
}

template<Scalar T>
Rectangle<T>::Rectangle(const Rectangle<T>& other) {
    points = std::make_unique<Point<T>[]>(RECTANGLE_ANGLES);
    for (size_t i = 0; i < RECTANGLE_ANGLES; ++i) {
        points[i] = other.points[i];
    }
}

template<Scalar T>
bool Rectangle<T>::Validate(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4) const {
    if (p1 == p2 || p1 == p3 || p1 == p4 ||
        p2 == p3 || p2 == p4 || p3 == p4) {
        return false;
    }

    T dx1 = p2.x - p1.x, dy1 = p2.y - p1.y;
    T dx2 = p3.x - p2.x, dy2 = p3.y - p2.y;
    T dx3 = p4.x - p3.x, dy3 = p4.y - p3.y;
    T dx4 = p1.x - p4.x, dy4 = p1.y - p4.y;

    bool parallel1 = std::abs(dx1 * dy3 - dy1 * dx3) < EPS;
    bool parallel2 = std::abs(dx2 * dy4 - dy2 * dx4) < EPS;

    bool perpendicular = std::abs(dx1 * dx2 + dy1 * dy2) < EPS;

    return parallel1 && parallel2 && perpendicular;
}

template<Scalar T>
Rectangle<T>& Rectangle<T>::operator=(const Rectangle<T>& other) {
    if (this != &other) {
        points = std::make_unique<Point<T>[]>(RECTANGLE_ANGLES);
        for (size_t i = 0; i < RECTANGLE_ANGLES; ++i) {
            points[i] = other.points[i];
        }
    }
    return *this;
}

template<Scalar T>
Rectangle<T>::Rectangle(Rectangle<T>&& other) noexcept 
    : points(std::move(other.points)) {
}

template<Scalar T>
Rectangle<T>& Rectangle<T>::operator=(Rectangle<T>&& other) noexcept {
    if (this != &other) {
        points = std::move(other.points);
    }
    return *this;
}

template<Scalar T>
Point<T> Rectangle<T>::Center() const {
    T center_x = (points[0].x + points[1].x + points[2].x + points[3].x) / 4.0;
    T center_y = (points[0].y + points[1].y + points[2].y + points[3].y) / 4.0;
    
    return Point<T>(center_x, center_y);
}

template<Scalar T>
double Rectangle<T>::Area() const {
    T width = std::sqrt(std::pow(points[0].x - points[1].x, 2) + std::pow(points[0].y - points[1].y, 2));
    T height = std::sqrt(std::pow(points[1].x - points[2].x, 2) + std::pow(points[1].y - points[2].y, 2));
    
    return width * height;
}

template<Scalar T>
Rectangle<T>::operator double() const {
    return Area();
}

template<Scalar U>
bool operator==(const Rectangle<U>& lf, const Rectangle<U>& rf) {
    
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
bool operator!=(const Rectangle<U>& lf, const Rectangle<U>& rf) {
    return !(lf == rf);
}

template<Scalar U>
std::ostream& operator<<(std::ostream& os, const Rectangle<U>& r) {
    for (size_t i = 0; i < RECTANGLE_ANGLES; ++i) {
        os << r.points[i].x << " " << r.points[i].y;
        if (i < 3) os << " ";
    }
    return os;
}

template<Scalar U>
std::istream& operator>>(std::istream& is, Rectangle<U>& r) {
    Point<U> points[SQUARE_ANGLES];
    for (size_t i = 0; i < SQUARE_ANGLES; ++i) {
        is >> points[i];
    }
    
    Rectangle<U> temp(points[0], points[1], points[2], points[3]);
    r = std::move(temp);
    
    return is;
}
}