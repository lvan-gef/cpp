/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   iterators_test.cpp                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/01 17:58:34 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/11/01 23:25:37 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
        assert(*it == expected && "Iter did not give the rigth element back");
        expected--;
    }

    // Test const iterator
    const MutantStack<int> &cms = ms;
    expected = 4;
    for (int cm : cms) {
        assert(cm == expected && "Const Iter did not give the rigth element back");
        expected--;
    }

    std::cout << "End Iterator Test" << '\n' << '\n';
}
