#pragma once

#include "figure.hpp"

namespace figure {

template<Scalar T>
class Triangle: public Figure<T> {
private:
    std::unique_ptr<Point<T>[]> points;

    bool Validate(Point<T> p1, Point<T> p2, Point<T> p3) const;
public:
    Triangle();
    Triangle(Point<T> p1, Point<T> p2, Point<T> p3);
    Triangle(const Triangle& other);
    Triangle(Triangle&& other) noexcept;
    Triangle<T>& operator=(const Triangle &other);
    Triangle<T>& operator=(Triangle &&other) noexcept;
    Point<T> Center() const override;
    double Area() const override;
    explicit operator double() const override;
    ~Triangle() = default;

template<Scalar U>
friend bool operator==(const Triangle<U>& first, const Triangle<U>& second);

template<Scalar U>
friend bool operator!=(const Triangle<U>& first, const Triangle<U>& second);

template<Scalar U>
friend std::ostream& operator<<(std::ostream& os, const Triangle<U>& r);

template<Scalar U>
friend std::istream& operator>>(std::istream& is, Triangle<U>& r);

};

}

#include "triangle.ipp"