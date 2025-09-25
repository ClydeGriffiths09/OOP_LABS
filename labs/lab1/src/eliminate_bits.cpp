#include <../include/eliminate_bits.h>

long eliminate_unset_bits(const std::string& number) {
    int count = 0;

    for (char symbol : number) {
        if (symbol == '1') {
            count++;
        }
    }

    if (count == 0) {
        return 0;
    }

    return (1L << count) - 1;
}