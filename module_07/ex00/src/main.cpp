#include "../include/Swap.hpp"
#include "../include/Min.hpp"
#include "../include/Max.hpp"
#include <cassert>
#include <iostream>

void subject_test() {
    int a = 2;
    int b = 3;
    std::string c = "chaine1";
    std::string d = "chaine2";

    int result = min(a, b);
    assert(result == a);

    result = max(a, b);
    assert(result == b);

    swap(a, b);
    assert(a == 3);
    assert(b == 2);

    std::string sResult = min(c, d);
    assert(sResult == c);

    sResult = max(c, d);
    assert(sResult == d);

    swap(c, d);
    assert(c == "chaine2");
    assert(d == "chaine1");
}

int main() {
    return 0;
}
