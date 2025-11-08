#pragma once

#include "figure.h"

namespace figure {

class Trapezoid: public Figure {
private:
    Point points[TRAPEZOIDANGLES];

    bool Validate(Point p1, Point p2, Point p3, Point p4) const;
    bool AreParallel(Point p1, Point p2, Point p3, Point p4) const;
    double CalculateHeight() const;
    static double PointToLineDistance(Point p, Point a, Point b);
public:
    Trapezoid();
    Trapezoid(Point p1, Point p2, Point p3, Point p4);
    Trapezoid(const Trapezoid& other);
    Trapezoid(Trapezoid&& other) noexcept;
    Trapezoid& operator=(const Trapezoid &other);
    Trapezoid& operator=(Trapezoid &&other) noexcept;
    Point Center() const override;
    double Area() const override;
    explicit operator double() const override;
    ~Trapezoid() = default;

friend bool operator==(const Trapezoid& first, const Trapezoid& second);
friend bool operator!=(const Trapezoid& first, const Trapezoid& second);
friend std::ostream& operator<<(std::ostream& os, const Trapezoid& r);
friend std::istream& operator>>(std::istream& is, Trapezoid& r);
};
}