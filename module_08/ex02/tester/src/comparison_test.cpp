#include "../include/tester.hpp"

void testComparisonOperators() {
    std::cout << "Start Comparison Test" << '\n';

    MutantStack<int> ms1;
    MutantStack<int> ms2;

    ms1.push(1);
    ms1.push(2);

    ms2.push(1);
    ms2.push(3);

    assert(ms1 != ms2);
    assert(ms1 < ms2);
    assert(ms1 <= ms2);
    assert(!(ms1 > ms2));
    assert(!(ms1 >= ms2));

    ms2 = ms1;
    assert(ms1 == ms2);
    assert(ms1 <= ms2);
    assert(ms1 >= ms2);

    std::cout << "Start Comparison Test" << '\n' << '\n';
}

