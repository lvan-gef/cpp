/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   containers_test.cpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/01 17:58:34 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/11/01 23:12:29 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.hpp"

void testWithDifferentContainers() {
    std::cout << "Start Containers Test" << '\n';

    // Test with std::list as container
    MutantStack<int, std::list<int>> ms_list;
    ms_list.push(1);
    ms_list.push(2);
    assert(ms_list.top() == 2 && "ms_list top element should be value 2");

    // Test with std::vector as container
    MutantStack<int, std::set<int>> ms_set;
    ms_set.push(1);
    ms_set.push(2);
    assert(ms_set.top() == 2 && "ms_set top element should be value 2");

    std::cout << "End Containers Test" << '\n' << '\n';
}
