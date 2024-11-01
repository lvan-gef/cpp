/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   swap_test.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/01 17:59:01 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/11/02 00:33:33 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.hpp"

void testSwap() {
    std::cout << "Start Swap Test" << '\n';

    MutantStack<int> ms1;
    MutantStack<int> ms2;

    ms1.push(1);
    ms1.push(2);

    ms2.push(3);
    ms2.push(4);
    ms2.push(5);

    size_t size1 = ms1.size();
    size_t size2 = ms2.size();

    ms1.swap(ms2);
    assert(ms1.size() == size2 && "ms1 size should be 3");
    assert(ms2.size() == size1 && "ms2 size should be 2");
    assert(ms1.top() == 5 && "ms1 top element should be value 5");
    assert(ms2.top() == 2 && "ms2 top element should be value 2");

    std::swap(ms2, ms1);
    assert(ms1.size() == size1 && "ms1 size should be 2");
    assert(ms2.size() == size2 && "ms2 size should be 3");
    assert(ms1.top() == 2 && "ms1 top element should be value 2");
    assert(ms2.top() == 5 && "ms2 top element should be value 5");

    std::cout << "Start Swap Test" << '\n' << '\n';
}
