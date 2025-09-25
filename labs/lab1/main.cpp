#include <eliminate_bits.h>
#include <iostream>

int main() {
    std::string input_number;
    std::cout << "Введеите двоичное число: ";
    std::cin >> input_number;

    for (char symbol : input_number) {
        if (symbol != '0' && symbol != '1') {
            std::cout << "Неверный формат!" << std::endl;
            return 0;
        }
    }

    long result = eliminate_unset_bits(input_number);

    std::cout << "Результат: " << result << std::endl;
    return 0;
}
