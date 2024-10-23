/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   opperators_test.cpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/23 21:43:01 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/23 21:43:01 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.hpp"

void testMax() {
    std::cout << "Start test for max function" << '\n';
    testBasicIntegersMax();
    testEqualIntegersMax();
    testNegativeIntegersMax();
    testIntegerLimitsMax();
    testFloatingPointMax();
    testStringsMax();
    testCharactersMax();
    testValueSemanticsMax();
    std::cout << "Passed test for max function" << '\n';
}

void testMin() {
    std::cout << "Start test for min function" << '\n';
    testBasicIntegersMin();
    testEqualIntegersMin();
    testNegativeIntegersMin();
    testIntegerLimitsMin();
    testFloatingPointMin();
    testStringsMin();
    testCharactersMin();
    testValueSemanticsMin();
    std::cout << "Passed test for min function" << '\n';
}

void testSwap() {
    std::cout << "Start test for swap function" << '\n';
    testBasicIntegers();
    testFloatingPoint();
    testCharacters();
    testStrings();
    testVectors();
    testCustomClass();
    testSameAddressProtection();
    testLargeStrings();
    testEmptyContainers();
    std::cout << "Passed test for swap function" << '\n';
}
