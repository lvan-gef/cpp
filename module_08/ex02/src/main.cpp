#include "../include/MutantStack.hpp"
#include <cassert>

static void subject_test() {
    MutantStack<int> mstack;
    mstack.push(5);
    assert(mstack.size() == 1 && "Stack should have 1 element inside it");
    assert(mstack.top() == 5 && "Stack top should be 5");

    mstack.push(17);
    assert(mstack.size() == 2 && "Stack should have 2 element inside it");
    assert(mstack.top() == 17 && "Stack top should be 17");

    mstack.pop();
    assert(mstack.size() == 1 && "Stack should have 1 element inside it");
    assert(mstack.top() == 5 && "Stack top should be 5");

    mstack.push(3);
    assert(mstack.size() == 2 && "Stack should have 2 element inside it");
    assert(mstack.top() == 3 && "Stack top should be 3");

    mstack.push(5);
    assert(mstack.size() == 3 && "Stack should have 3 element inside it");
    assert(mstack.top() == 5 && "Stack top should be 5");

    mstack.push(737);
    assert(mstack.size() == 4 && "Stack should have 4 element inside it");
    assert(mstack.top() == 737 && "Stack top should be 737");

    mstack.push(0);
    assert(mstack.size() == 5 && "Stack should have 5 element inside it");
    assert(mstack.top() == 0 && "Stack top should be 0");

    MutantStack<int>::iterator it = mstack.begin();
    assert(*it == 5 && "it begin should be 5");
    ++it;
    assert(*it == 3 && "it begin should be 3");
    --it;
    assert(*it == 5 && "it begin should be 5");

    MutantStack<int>::iterator ite = mstack.end();
    while (it != ite) {
        std::cout << *it << std::endl;
        ++ite;
    }
    // std::stack<int> s(mstack);
}

int main() {
    subject_test();
    return 0;
}
