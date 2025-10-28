#include "rectangle.h"
#include "trapezoid.h"
#include "rhombus.h"

#include <iostream>

int main() {
    using namespace figure;
    
    Point p(1.5, 2.5);
    std::cout << "Point: " << p << std::endl;
    
    Rectangle rect(Point(0,0), Point(0,2), Point(3,2), Point(3,0));
    std::cout << "Rectangle: " << rect << std::endl;
    
    return 0;
}