#include "triangle.hpp"
#include "exceptions.hpp"

namespace figure {

template<Scalar T>
Triangle<T>::Triangle() {
    points = std::make_unique<Point<T>[]>(TRIANGLE_ANGLES);
    points[0] = Point<T>(0, 0);
    points[1] = Point<T>(1, 0);
    points[2] = Point<T>(1, 1);
}

template<Scalar T>
Triangle<T>::Triangle(Point<T> p1, Point<T> p2, Point<T> p3){
    if (!Validate(p1, p2, p3)) {
        throw exceptions::InvalidPointsException("Invalid points to create a Triangle");
    }

    points = std::make_unique<Point<T>[]>(TRIANGLE_ANGLES);
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
}

template<Scalar T>
Triangle<T>::Triangle(const Triangle<T>& other) {
    points = std::make_unique<Point<T>[]>(TRIANGLE_ANGLES);
    for (size_t i = 0; i < TRIANGLE_ANGLES; ++i) {
        points[i] = other.points[i];
    }
}

template<Scalar T>
bool Triangle<T>::Validate(Point<T> p1, Point<T> p2, Point<T> p3) const {
    if (p1 == p2 || p1 == p3 || p2 == p3) {
        return false;
    }
    
    T area = std::abs((p1.x*(p2.y-p3.y) + p2.x*(p3.y-p1.y) + p3.x*(p1.y-p2.y)) / 2.0);
    return area > EPS;
}

template<Scalar T>
Triangle<T>& Triangle<T>::operator=(const Triangle<T>& other) {
    if (this != &other) {
        points = std::make_unique<Point<T>[]>(TRIANGLE_ANGLES);
        for (size_t i = 0; i < TRIANGLE_ANGLES; ++i) {
            points[i] = other.points[i];
        }
    }
    return *this;
}

template<Scalar T>
Triangle<T>::Triangle(Triangle<T>&& other) noexcept 
    : points(std::move(other.points)) {
}

template<Scalar T>
Triangle<T>& Triangle<T>::operator=(Triangle<T>&& other) noexcept {
    if (this != &other) {
        points = std::move(other.points);
    }
    return *this;
}

template<Scalar T>
Point<T> Triangle<T>::Center() const {
    T center_x = (points[0].x + points[1].x + points[2].x) / 3;
    T center_y = (points[0].y + points[1].y + points[2].y) / 3;
    return Point<T>(center_x, center_y);
}

template<Scalar T>
double Triangle<T>::Area() const {
    T x1 = points[0].x, y1 = points[0].y;
    T x2 = points[1].x, y2 = points[1].y;
    T x3 = points[2].x, y3 = points[2].y;
    
    return std::abs((x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2)) / 2.0);
}

template<Scalar T>
Triangle<T>::operator double() const {
    return Area();
}

template<Scalar U>
bool operator==(const Triangle<U>& first, const Triangle<U>& second) {
    return std::abs(static_cast<double>(first) - static_cast<double>(second)) < EPS;
}

template<Scalar U>
bool operator!=(const Triangle<U>& first, const Triangle<U>& second) {
    return !(first == second);
}

template<Scalar U>
std::ostream& operator<<(std::ostream& os, const Triangle<U>& r) {
    for (size_t i = 0; i < TRIANGLE_ANGLES; ++i) {
        os << r.points[i].x << " " << r.points[i].y;
        if (i < 2) os << " ";
    }
    return os;
}

template<Scalar U>
std::istream& operator>>(std::istream& is, Triangle<U>& r) {
    Point<U> points[TRIANGLE_ANGLES];
    for (size_t i = 0; i < TRIANGLE_ANGLES; ++i) {
        is >> points[i];
    }
    
    Triangle<U> temp(points[0], points[1], points[2]);
    r = std::move(temp);
    
    return is;
}
}