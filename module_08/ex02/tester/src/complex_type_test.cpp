#include "../include/tester.hpp"

void testComplexTypes() {
    std::cout << "Start ComplexType Operations Test" << '\n';

    MutantStack<std::vector<int>> ms_vec;
    std::stack<std::vector<int>> og_vec;

    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {4, 5, 6};

    assert(ms_vec.empty() == true && "ms_vec should be empty");
    ms_vec.push(v1);
    ms_vec.push(v2);
    assert(ms_vec.empty() != true && "ms_vec should not be empty");
    assert(ms_vec.size() == 2 && "ms_vec should be size 2");
    assert(ms_vec.top() == v2 && "ms_vec should be {4, 5, 6}");

    assert(og_vec.empty() == true && "og_vec should be empty");
    og_vec.push(v1);
    og_vec.push(v2);
    assert(og_vec.empty() != true && "og_vec should not be empty");
    assert(og_vec.size() == 2 && "og_vec should be size 2");
    assert(og_vec.top() == v2 && "og_vec should be {4, 5, 6}");

    assert(ms_vec.size() == og_vec.size() && "Own and Og should be the same size: 2");
    assert(ms_vec.top() == og_vec.top() && "Own and Og should be the seem: {4, 5, 6}");

    ms_vec.pop();
    assert(ms_vec.empty() != true && "ms_vec should not be empty");
    assert(ms_vec.size() == 1 && "ms_vec should be size 1");
    assert(ms_vec.top() == v1 && "ms_vec should be {1, 2, 3}");

    og_vec.pop();
    assert(og_vec.empty() != true && "og_vec should not be empty");
    assert(og_vec.size() == 1 && "og_vec should be size 1");
    assert(og_vec.top() == v1 && "og_vec should be {1, 2, 3}");

    ms_vec.pop();
    assert(ms_vec.empty() == true && "ms_vec should be empty");

    og_vec.pop();
    assert(og_vec.empty() == true && "og_vec should be empty");


    // MutantStack<ComplexType> ms_complex;
    // ms_complex.push(ComplexType("first", {1, 2, 3}));
    // ms_complex.push(ComplexType("second", {4, 5, 6}));
    //
    // std::vector<int> expected1 = {4, 5, 6};
    // assert(ms_complex.top().name == "second" && "Expect name to be 'first'");
    // assert(ms_complex.top().data == expected1 && "Expect data to be {1, 2, 3}");
    //
    // ms_complex.pop();
    // assert(ms_complex.size() == 1 && "Expect that ms_complex.size() == 1");
    //
    // std::vector<int> expected = {1, 2, 3};
    // assert(ms_complex.top().name == "first" && "Expect name to be 'first'");
    // assert(ms_complex.top().data == expected && "Expect data to be {1, 2, 3}");
    //
    // ms_complex.pop();
    // assert(ms_complex.size() == 0 && "Expect that ms_complex.size() == 0");

    std::cout << "End ComplexType Operations Test" << '\n';
}
