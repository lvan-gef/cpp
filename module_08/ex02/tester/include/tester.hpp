/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 17:42:51 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/11/01 17:52:33 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_HPP
#define TESTER_HPP

#include "../../include/MutantStack.hpp"

#include <cassert>
#include <stack>
#include <vector>
#include <list>
#include <set>

// Complex type for testing
struct ComplexType {
    std::vector<int> data;
    std::string name;

    ComplexType(const std::string& n = "", std::initializer_list<int> d = {})
        : data(d), name(n) {}

    bool operator==(const ComplexType& rhs) const {
        return data == rhs.data && name == rhs.name;
    }

    bool operator<(const ComplexType& rhs) const {
        return name < rhs.name || (name == rhs.name && data < rhs.data);
    }
};

void testMutantStack();

void testSubject();
void testBasicOperations();
void testComplexTypes();
void testConstructorsAndAssignment();
void testIterators();
void testComparisonOperators();
void testWithDifferentContainers();
void testEmplace();
void testSwap();

#endif // TESTER_HPP
