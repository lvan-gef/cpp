#ifndef TESTER_HPP
#define TESTER_HPP

#include "../../include/Max.hpp"
#include "../../include/Min.hpp"
#include "../../include/Swap.hpp"

#include <cassert>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

// max tester
void testBasicIntegersMax();
void testEqualIntegersMax();
void testNegativeIntegersMax();
void testIntegerLimitsMax();
void testFloatingPointMax();
void testStringsMax();
void testCharactersMax();
void testValueSemanticsMax();
void testMax();

// min tester
void testBasicIntegersMin();
void testEqualIntegersMin();
void testNegativeIntegersMin();
void testIntegerLimitsMin();
void testFloatingPointMin();
void testStringsMin();
void testCharactersMin();
void testValueSemanticsMin();
void testMin();

// swap tester
// Helper function to verify swap was successful
template <typename T>
static void verifySwap(const T &originalA, const T &originalB, const T &newA,
                       const T &newB, const char *message) {
    assert(newA == originalB && newB == originalA && message);
}

// Simple custom class for testing
class TestClass {
  public:
    TestClass(int v = 0) : value(v) {}
    bool operator==(const TestClass &other) const {
        return value == other.value;
    }
    int value;
};

void testBasicIntegers();
void testFloatingPoint();
void testCharacters();
void testStrings();
void testVectors();
void testCustomClass();
void testSameAddressProtection();
void testLargeStrings();
void testEmptyContainers();
void testSwap();

#endif // TESTER_HPP
