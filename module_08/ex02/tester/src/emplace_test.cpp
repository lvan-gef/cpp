/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   emplace_test.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/01 17:58:34 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/11/01 23:13:22 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.hpp"

void testEmplace() {
    std::cout << "Start Emplace Test" << '\n';

    MutantStack<ComplexType> ms;
    std::vector<int> expect{1, 2, 3};
    ms.emplace("test", std::initializer_list<int>{1, 2, 3});

    assert(ms.top().name == "test" && "Emplace top element name should be: 'test'");
    assert(ms.top().data == expect && "Emplace top data should be: {1, 2, 3}");

    std::cout << "Start Emplace Test" << '\n' << '\n';
}
