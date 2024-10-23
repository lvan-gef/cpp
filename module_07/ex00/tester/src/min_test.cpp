#include "../include/tester.hpp"

void testBasicIntegersMin() {
    int a = 5, b = 3;
    assert(min(a, b) == 3 && "Basic integers (5,3) failed");

    a = 3;
    b = 5;
    assert(min(a, b) == 3 && "Basic integers (3,5) failed");

    // Test zero handling
    a = 0;
    b = 1;
    assert(min(a, b) == 0 && "Zero comparison failed");
}

void testEqualIntegersMin() {
    int a = 5, b = 5;
    assert(min(a, b) == 5 && "Equal integers failed");

    // Original values should remain unchanged
    assert(a == 5 && b == 5 && "Equal integers modified original values");

    // Test with zero
    a = 0;
    b = 0;
    assert(min(a, b) == 0 && "Equal zeros failed");
}

void testNegativeIntegersMin() {
    int a = -5, b = -3;
    assert(min(a, b) == -5 && "Negative integers failed");

    a = -5;
    b = 3;
    assert(min(a, b) == -5 && "Mixed sign integers failed");

    a = -3;
    b = -5;
    assert(min(a, b) == -5 && "Reversed negative integers failed");
}

void testIntegerLimitsMin() {
    int a = std::numeric_limits<int>::max();
    int b = std::numeric_limits<int>::min();
    assert(min(a, b) == std::numeric_limits<int>::min() &&
           "Integer limits failed");

    // Test near minimum values
    a = std::numeric_limits<int>::min();
    b = std::numeric_limits<int>::min() + 1;
    assert(min(a, b) == std::numeric_limits<int>::min() &&
           "Near minimum integers failed");
}

void testFloatingPointMin() {
    double a = 3.14, b = 2.718;
    assert(min(a, b) == 2.718 && "Basic floating point failed");

    // Test very close values
    a = 1.0000001;
    b = 1.0000000;
    assert(min(a, b) == 1.0000000 && "Small difference floating point failed");

    // Test negative floating points
    a = -3.14;
    b = -2.718;
    assert(min(a, b) == -3.14 && "Negative floating point failed");

    // Test with zero
    a = 0.0;
    b = -0.0;
    assert(min(a, b) == -0.0 && "Zero floating point failed");
}

void testStringsMin() {
    std::string a = "hello";
    std::string b = "world";
    assert(min(a, b) == "hello" && "Basic strings failed");

    // Test empty string
    a = "";
    b = "a";
    assert(min(a, b) == "" && "Empty string failed");

    // Test same prefix
    a = "abc";
    b = "abcd";
    assert(min(a, b) == "abc" && "String prefix comparison failed");

    // Test case sensitivity
    a = "ABC";
    b = "abc";
    assert(min(a, b) == "ABC" && "String case sensitivity failed");
}

void testCharactersMin() {
    char a = 'b', b = 'a';
    assert(min(a, b) == 'a' && "Basic characters failed");

    // Test case sensitivity
    a = 'A';
    b = 'a';
    assert(min(a, b) == 'A' && "Case sensitive characters failed");

    // Test with special characters
    a = '!';
    b = '~';
    assert(min(a, b) == '!' && "Special characters failed");

    // Test with space
    a = ' ';
    b = 'a';
    assert(min(a, b) == ' ' && "Space character failed");
}

void testValueSemanticsMin() {
    // Test that modifying the return value doesn't affect originals
    int a = 5, b = 3;
    int result = min(a, b);
    result = 10;
    assert(a == 5 && "Original value a was modified");
    assert(b == 3 && "Original value b was modified");

    // Test with strings
    std::string str1 = "hello";
    std::string str2 = "world";
    std::string strResult = min(str1, str2);
    strResult = "modified";
    assert(str1 == "hello" && "Original string1 was modified");
    assert(str2 == "world" && "Original string2 was modified");

    // Test with characters
    char c1 = 'a', c2 = 'b';
    char charResult = min(c1, c2);
    charResult = 'x';
    assert(c1 == 'a' && "Original char1 was modified");
    assert(c2 == 'b' && "Original char2 was modified");
}
