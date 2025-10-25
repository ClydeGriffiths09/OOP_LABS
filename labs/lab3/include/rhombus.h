#pragma once

#include "figure.h"

namespace figure {
    class Rhombus: public Figure {
        private:
            Point* points[ANGLES];

            bool Validate(Point p1, Point p2, Point p3, Point p4) const;
            void Clear();
        public:
            Rhombus();
            Rhombus(Point p1, Point p2, Point p3, Point p4);
            Rhombus(const Rhombus& other);
            Rhombus(Rhombus&& other) noexcept;
            Rhombus& operator=(const Rhombus &other);
            Rhombus& operator=(Rhombus &&other) noexcept;
            Point Center() const override;
            double Area() const override;
            explicit operator double() const override;
            ~Rhombus();
        
        friend bool operator==(const Rhombus& first, const Rhombus& second);
        friend bool operator!=(const Rhombus& first, const Rhombus& second);
        friend std::ostream& operator<<(std::ostream& os, const Rhombus& r);
        friend std::istream& operator>>(std::istream& is, Rhombus& r);
    };
}