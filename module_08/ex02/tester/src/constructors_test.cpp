/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   constructors_test.cpp                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/01 17:58:33 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/11/01 23:06:28 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.hpp"

void testConstructorsAndAssignment() {
    std::cout << "Start Constructor Test" << '\n';

    // Default constructor
    MutantStack<int> ms1;
    ms1.push(1);
    ms1.push(2);

    // Copy constructor
    MutantStack<int> ms2(ms1);
    assert(ms2.size() == ms1.size() && "ms1 and ms2 should have 2 elements");
    assert(ms2.top() == ms1.top() &&
           "ms1 and ms2 top element should be value 2");

    // Assignment operator
    MutantStack<int> ms3;
    ms3 = ms1;
    assert(ms3.size() == ms1.size() && "ms1 and ms3 should have 2 elements");
    assert(ms3.top() == ms1.top() &&
           "ms1 and ms3 top element should be value 2");

    // Move constructor
    MutantStack<int> ms4(std::move(ms1));
    assert(ms4.size() == 2 && "ms4 sould have 2 elements");
    assert(ms4.top() == 2 && "ms4 top elements should be value 2");

    // Move assignment
    MutantStack<int> ms5;
    ms5 = std::move(ms4);
    assert(ms5.size() == 2 && "ms5 should have 2 elements");
    assert(ms5.top() == 2 && "ms5 top element shoulb be value 2");

    std::cout << "End Constructor Test" << '\n' << '\n';
}
