#include "../include/tester.hpp"

void testIterators() {
    std::cout << "Start Iterator Test" << '\n';

    MutantStack<int> ms;
    for (int i = 0; i < 5; ++i) {
        ms.push(i);
    }

    // Test iterator functionality
    int expected = 4;
    for (auto it = ms.begin(); it != ms.end(); ++it) {
        assert(*it == expected--);
    }

    // Test const iterator
    const MutantStack<int>& cms = ms;
    expected = 4;
    for (int cm : cms) {
        assert(cm == expected--);
    }

    std::cout << "End Iterator Test" << '\n' << '\n';
}
