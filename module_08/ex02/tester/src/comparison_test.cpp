/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   comparison_test.cpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/01 17:58:33 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/11/02 00:12:52 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.hpp"

void testComparisonOperators() {
    std::cout << "Start Comparison Test" << '\n';

    MutantStack<int> ms1;
    MutantStack<int> ms2;

    ms1.push(1);
    ms1.push(2);

    ms2.push(1);
    ms2.push(3);

    assert(ms1 != ms2 && "ms1 should not be eq to ms2");

    assert(ms1 < ms2 && "ms1 should be less then ms2");
    assert(ms1 <= ms2 && "ms1 should be less then ms2");
    ms2.pop();
    ms2.push(2);
    assert(ms1 <= ms2 && "ms1 should be eq to ms2");

    ms2.pop();
    ms2.push(3);
    assert(ms2 > ms1 && "ms2 should be more then ms1");
    assert(ms2 >= ms1 && "ms2 should be more then ms1");
    ms2.pop();
    ms2.push(2);
    assert(ms2 >= ms1 && "ms2 should be eq to ms1");

    ms2 = ms1;
    assert(ms1 == ms2 && "ms1 should be eq bs2");

    std::cout << "Start Comparison Test" << '\n' << '\n';
}
