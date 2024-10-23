#include "../include/tester.hpp"

void testBasicIntegersMax() {
    // Test case: regular integers
    int a = 5, b = 3;
    assert(max(a, b) == 5 && "Basic integers (5,3) failed");

    // Test case: reverse order
    a = 3;
    b = 5;
    assert(max(a, b) == 5 && "Basic integers (3,5) failed");
}

void testEqualIntegersMax() {
    int a = 5, b = 5;
    assert(max(a, b) == 5 && "Equal integers failed");

    // Verify that both values are unchanged
    assert(a == 5 && b == 5 && "Equal integers modified original values");
}

void testNegativeIntegersMax() {
    // Test case: both negative
    int a = -5, b = -3;
    assert(max(a, b) == -3 && "Negative integers failed");

    // Test case: mixed signs
    a = -5;
    b = 3;
    assert(max(a, b) == 3 && "Mixed sign integers failed");
}

void testIntegerLimitsMax() {
    // Test case: maximum and minimum integers
    int a = std::numeric_limits<int>::max();
    int b = std::numeric_limits<int>::min();
    assert(max(a, b) == std::numeric_limits<int>::max() &&
           "Integer limits failed");

    // Test case: near maximum values
    a = std::numeric_limits<int>::max();
    b = std::numeric_limits<int>::max() - 1;
    assert(max(a, b) == std::numeric_limits<int>::max() &&
           "Near maximum integers failed");
}

void testFloatingPointMax() {
    // Test case: regular floating point
    double a = 3.14, b = 2.718;
    assert(max(a, b) == 3.14 && "Basic floating point failed");

    // Test case: very close values
    a = 1.0000001;
    b = 1.0000000;
    assert(max(a, b) == 1.0000001 && "Small difference floating point failed");

    // Test case: negative floating point
    a = -3.14;
    b = -2.718;
    assert(max(a, b) == -2.718 && "Negative floating point failed");
}

void testStringsMax() {
    // Test case: regular strings
    std::string a = "hello";
    std::string b = "world";
    assert(max(a, b) == "world" && "Basic strings failed");

    // Test case: empty string
    a = "";
    b = "a";
    assert(max(a, b) == "a" && "Empty string failed");

    // Test case: same length, different content
    a = "abc";
    b = "abd";
    assert(max(a, b) == "abd" && "Same length strings failed");
}

void testCharactersMax() {
    // Test case: regular characters
    char a = 'a', b = 'b';
    assert(max(a, b) == 'b' && "Basic characters failed");

    // Test case: case sensitivity
    a = 'A';
    b = 'a';
    assert(max(a, b) == 'a' && "Case sensitive characters failed");

    // Test case: special characters
    a = '!';
    b = '~';
    assert(max(a, b) == '~' && "Special characters failed");
}

void testValueSemanticsMax() {
    // Test that modifying the return value doesn't affect originals
    int a = 5, b = 3;
    int result = max(a, b);
    result = 10;
    assert(a == 5 && "Original value a was modified");
    assert(b == 3 && "Original value b was modified");

    // Test with strings
    std::string str1 = "hello";
    std::string str2 = "world";
    std::string strResult = max(str1, str2);
    strResult = "modified";
    assert(str1 == "hello" && "Original string1 was modified");
    assert(str2 == "world" && "Original string2 was modified");
}
