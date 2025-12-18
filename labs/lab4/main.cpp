#include "exceptions.hpp"
#include "rectangle.hpp"
#include "square.hpp"
#include "triangle.hpp"

int main() {
    figure::Square<float> s;
    std::cout << "Enter the square points:" << std::endl;
    std::cin >> s;

    figure::Rectangle<int> r;
    std::cout << "Enter the rectangle points:" << std::endl;
    std::cin >> r;

    figure::Triangle<double> t;
    std::cout << "Enter the triangle points:" << std::endl;
    std::cin >> t;

    std::cout << "Square: " << s << std::endl;
    std::cout << "Rectangle: " << r << std::endl;
    std::cout << "Triangle: " << t << std::endl;
    return 0;
}