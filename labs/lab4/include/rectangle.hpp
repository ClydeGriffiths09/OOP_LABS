#pragma once

#include "figure.hpp"

namespace figure {

template<Scalar T>
class Rectangle: public Figure<T> {
private:
    std::unique_ptr<Point<T>[]> points;

    bool Validate(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4) const;
public:
    Rectangle();
    Rectangle(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4);
    Rectangle(const Rectangle& other);
    Rectangle(Rectangle&& other) noexcept;
    Rectangle<T>& operator=(const Rectangle &other);
    Rectangle<T>& operator=(Rectangle &&other) noexcept;
    Point<T> Center() const override;
    double Area() const override;
    explicit operator double() const override;
    ~Rectangle() = default;

template<Scalar U>
friend bool operator==(const Rectangle<U>& first, const Rectangle<U>& second);

template<Scalar U>
friend bool operator!=(const Rectangle<U>& first, const Rectangle<U>& second);

template<Scalar U>
friend std::ostream& operator<<(std::ostream& os, const Rectangle<U>& r);

template<Scalar U>
friend std::istream& operator>>(std::istream& is, Rectangle<U>& r);

};

}

#include "rectangle.ipp"