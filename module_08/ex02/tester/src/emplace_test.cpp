#include "../include/tester.hpp"

void testEmplace() {
    std::cout << "Start Emplace Test" << '\n';

    MutantStack<ComplexType> ms;
    std::vector<int> expect{1, 2, 3};
    ms.emplace("test", std::initializer_list<int>{1, 2, 3});

    assert(ms.top().name == "test");
    assert(ms.top().data == expect);

    std::cout << "Start Emplace Test" << '\n' << '\n';
}
