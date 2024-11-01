/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   basic_test.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/01 17:58:29 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/11/01 23:21:03 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.hpp"

void testBasicOperations() {
    std::cout << "Start Basic Operations Test" << '\n';

    MutantStack<int> ms;
    std::stack<int> ss;

    // Test empty
    assert(ms.empty() == ss.empty() &&
           "ms should be empty, also ss should be empty");
    assert(ms.size() == ss.size() && "ms should be 0, also ss should be 0");

    // Test push and size
    ms.push(1);
    ss.push(1);
    assert(ms.size() == ss.size() &&
           "ms should be size 1, also ss should be size 1");
    assert(ms.top() == ss.top() &&
           "ms.top() should be 1, also ss.top() should be 1");

    // Test pop
    ms.pop();
    ss.pop();
    assert(ms.empty() == ss.empty() &&
           "ms should be empty, also ss should be empty");
    assert(ms.size() == ss.size() && "ms should be 0, also ss should be 0");

    std::cout << "End Basic Operations Test" << '\n' << '\n';
}
