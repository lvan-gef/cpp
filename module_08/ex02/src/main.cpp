/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/01 17:57:20 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/11/01 17:57:35 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MutantStack.hpp"
#include "../tester/include/tester.hpp"
#include <cassert>
#include <stack>

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

    auto it = mstack.begin();
    assert(*it == 0 && "it begin should be 0");

    ++it;
    assert(*it == 737 && "it begin should be 737");

    --it;
    assert(*it == 0 && "it begin should be 0");

    ++it;
    assert(*it == 737 && "it begin should be 737");

    ++it;
    assert(*it == 5 && "it begin should be 5");

    ++it;
    assert(*it == 3 && "it begin should be 3");

    ++it;
    assert(*it == 5 && "it begin should be 5");

    std::stack<int> s(mstack);
    s.push(1);
    assert(s.size() == 6 && "s should have 6 element inside it");
    assert(s.top() == 1 && "s top should be 1");
    assert(mstack.size() == 5 &&
           "mstack should still have 5 elements inside it");
}

int main() {
    subject_test();

    testMutantStack();
    return 0;
}
