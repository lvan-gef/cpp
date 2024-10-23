/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   iter_test.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/23 21:43:33 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/23 21:43:33 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.hpp"

void testIter() {
    try {
        testIntegerArray();
        testDoubleArray();
        testCharArray();
        testCStyleString();
        testNullptr();
        testZeroSize();
        testEmptyArray();
        testCustomType();
        testExceptionPropagation();
        testLargeArray();
        testMultipleFunctionTypes();

        testOversizedCString();
        testOversizedWithNullTerminator();
        // testOversizedIntArray();        // UB
        // testOversizedCharArray();       // UB
        // testOversizedCustomType();      // UB
    } catch (const std::exception &e) {
        std::cerr << "Unexpected exception in testIter: " << e.what()
                  << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception in testIter" << std::endl;
    }
}
