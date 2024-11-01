/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutantStack_test.cpp                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/01 17:58:34 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/11/01 17:58:51 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.hpp"

void testMutantStack() {
    testSubject();
    testBasicOperations();
    testComplexTypes();
    testConstructorsAndAssignment();
    testIterators();
    testComparisonOperators();
    testWithDifferentContainers();
    testEmplace();
    testSwap();
}
