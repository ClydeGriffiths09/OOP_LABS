#pragma once

#include "figure.hpp"

namespace figure {

template<Scalar T>
class Square: public Figure<T> {
private:
    std::unique_ptr<Point<T>[]> points;

    bool Validate(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4) const;
public:
    Square();
    Square(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4);
    Square(const Square& other);
    Square(Square&& other) noexcept;
    Square<T>& operator=(const Square &other);
    Square<T>& operator=(Square &&other) noexcept;
    Point<T> Center() const override;
    double Area() const override;
    explicit operator double() const override;
    ~Square() = default;

template<Scalar U>
friend bool operator==(const Square<U>& first, const Square<U>& second);

template<Scalar U>
friend bool operator!=(const Square<U>& first, const Square<U>& second);

template<Scalar U>
friend std::ostream& operator<<(std::ostream& os, const Square<U>& r);

template<Scalar U>
friend std::istream& operator>>(std::istream& is, Square<U>& r);

};

}

#include "square.ipp"