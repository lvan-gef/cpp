#include "../include/tester.hpp"

void testConstructorsAndAssignment() {

    // Default constructor
    MutantStack<int> ms1;
    ms1.push(1);
    ms1.push(2);

    // Copy constructor
    MutantStack<int> ms2(ms1);
    assert(ms2.size() == ms1.size());
    assert(ms2.top() == ms1.top());

    // Assignment operator
    MutantStack<int> ms3;
    ms3 = ms1;
    assert(ms3.size() == ms1.size());
    assert(ms3.top() == ms1.top());

    // Move constructor
    MutantStack<int> ms4(std::move(ms1));
    assert(ms4.size() == 2);
    assert(ms4.top() == 2);

    // Move assignment
    MutantStack<int> ms5;
    ms5 = std::move(ms4);
    assert(ms5.size() == 2);
    assert(ms5.top() == 2);
}
