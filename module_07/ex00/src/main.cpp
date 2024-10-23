#include "../include/Max.hpp"
#include "../include/Min.hpp"
#include "../include/Swap.hpp"
#include <iostream>

void subject_test() {
    int a = 2;
    int b = 3;
    swap(a, b);
    std::cout << "a = " << a << ", b = " << b << '\n';
    std::cout << "min( a, b ) = " << min(a, b) << '\n';
    std::cout << "max( a, b ) = " << max(a, b) << '\n';
    std::string c = "chaine1";
    std::string d = "chaine2";
    swap(c, d);
    std::cout << "c = " << c << ", d = " << d << '\n';
    std::cout << "min( c, d ) = " << min(c, d) << '\n';
    std::cout << "max( c, d ) = " << max(c, d) << '\n';
}

int main() {
    subject_test();
    return 0;
}
