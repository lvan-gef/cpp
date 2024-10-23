/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/23 21:43:19 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/23 21:43:19 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_HPP
#define TESTER_HPP

#include <iostream>
#include <cassert>
#include <cstring>
#include <functional>

#include "../../include/iter.hpp"

struct TestStruct {
    int value;
    bool operator==(char null) const {
        (void)null;
        return false;
    } // For null check in iter
};

// Custom type that doesn't trigger undefined behavior
struct SafeTestStruct {
    int value;
    bool operator==(char null) const {
        (void)null;
        return value == 0;  // Treats 0 as null
    }
};

void modifySafeStruct(SafeTestStruct& ts);
void modifyTestStruct(TestStruct &ts);

// Test functions to pass to iter
void incrementInt(int& n);
void multiplyByTwo(double& n);
void toUpperCase(char& c);
void throwingFunction(int & /*n*/);
void modifyTestStruct(TestStruct &ts);

// testers
void testIntegerArray();
void testDoubleArray();
void testCharArray();
void testCStyleString();
void testNullptr();
void testZeroSize();
void testEmptyArray();
void testCustomType();
void testExceptionPropagation();
void testLargeArray();
void testMultipleFunctionTypes();

// maybe UB
void testOversizedIntArray();
void testOversizedCharArray();
void testOversizedCString();
void testOversizedWithNullTerminator();
void testOversizedCustomType();

void testIter();
#endif // TESTER_HPP
