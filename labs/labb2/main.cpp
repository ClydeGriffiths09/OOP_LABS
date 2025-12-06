#include <vector.h>
#include <eleven.h>

int main() {
    std::string input_number1;
    std::string input_number2;
    std::cin >> input_number1;
    std::cin >> input_number2;
    eleven::Eleven e1(input_number1);
    eleven::Eleven e2(input_number2);
    eleven::Eleven result = eleven::Eleven::Add(e1, e2);
    std::cout << result.ToString() << std::endl;
    return 0;
}