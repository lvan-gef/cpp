/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   emplace_test.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/01 17:58:34 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/11/02 00:30:44 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.hpp"

void testEmplace() {
    std::cout << "Start Emplace Test" << '\n';

    MutantStack<ComplexType> ms;
    std::stack<ComplexType> og;

    std::vector<int> expect{1, 2, 3};
    std::vector<int> expect1{42};

    ms.push(ComplexType("Luuk", std::initializer_list<int>{42}));
    assert(ms.top().name == "Luuk" && "ms top element name should be: 'test'");
    assert(ms.top().data == expect1 && "ms top data should be: {1, 2, 3}");

    og.push(ComplexType("Luuk", std::initializer_list<int>{42}));
    assert(og.top().name == "Luuk" && "og top element name should be: 'test'");
    assert(og.top().data == expect1 && "og top data should be: {1, 2, 3}");

    ms.emplace("test", std::initializer_list<int>{1, 2, 3});
    assert(ms.top().name == "test" && "ms Emplace top element name should be: 'test'");
    assert(ms.top().data == expect && "ms Emplace top data should be: {1, 2, 3}");

    og.emplace("test", std::initializer_list<int>{1, 2, 3});
    assert(og.top().name == "test" && "og Emplace top element name should be: 'test'");
    assert(og.top().data == expect && "og Emplace top data should be: {1, 2, 3}");

    std::cout << "Start Emplace Test" << '\n' << '\n';
}
