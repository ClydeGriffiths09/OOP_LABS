#pragma once

#include "figure.h"

namespace figure {
    class Rectangle: public Figure {
        private:
            Point* points[ANGLES];

            bool Validate(Point p1, Point p2, Point p3, Point p4) const;
            void Clear();
        public:
            Rectangle();
            Rectangle(Point p1, Point p2, Point p3, Point p4);
            Rectangle(const Rectangle& other);
            Rectangle(Rectangle&& other) noexcept;
            Rectangle& operator=(const Rectangle &other);
            Rectangle& operator=(Rectangle &&other) noexcept;
            Point Center() const override;
            double Area() const override;
            explicit operator double() const override;
            ~Rectangle();
        
        friend bool operator==(const Rectangle& first, const Rectangle& second);
        friend bool operator!=(const Rectangle& first, const Rectangle& second);
        friend std::ostream& operator<<(std::ostream& os, const Rectangle& r);
        friend std::istream& operator>>(std::istream& is, Rectangle& r);
    };
}