/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 17:42:51 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/11/02 01:32:19 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_HPP
#define TESTER_HPP

#include <cassert>
#include <deque>
#include <iostream>
#include <list>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

#include "../../include/easyfind.hpp"

// Helper function to run a test case and report results
template <typename T>
void runTest(T container, int target, bool shouldSucceed) {
    try {
        easyfind(container, target);
        if (shouldSucceed) {
            std::cout << "✓ Test passed: Found target " << target << std::endl;
        } else {
            std::cout << "✗ Test failed: Expected exception but found target"
                      << '\n';
            assert(false);
        }
    } catch (const std::invalid_argument &e) {
        if (!shouldSucceed) {
            std::cout
                << "✓ Test passed: Correctly throw exception for missing target"
                << '\n';
        } else {
            std::cout << "✗ Test failed: Unexpected exception - " << e.what()
                      << '\n';
            assert(false);
        }
    } catch (...) {
        std::cout << "✗ Test failed: Unexpected exception type" << std::endl;
        assert(false);
    }
}
int testEasyFind();

void testVector();
void testList();
void testDeque();
void testSet();
void testEdgeCases();

#endif // TESTER_HPP
