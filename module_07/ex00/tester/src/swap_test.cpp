#include "../include/tester.hpp"

void testBasicIntegers() {
    // Test regular integers
    int a = 5, b = 3;
    int origA = a, origB = b;
    swap(a, b);
    verifySwap(origA, origB, a, b, "Basic integer swap failed");

    // Test with zero
    a = 0;
    b = 42;
    origA = a;
    origB = b;
    swap(a, b);
    verifySwap(origA, origB, a, b, "Zero integer swap failed");

    // Test negative numbers
    a = -5;
    b = -3;
    origA = a;
    origB = b;
    swap(a, b);
    verifySwap(origA, origB, a, b, "Negative integer swap failed");
}

void testFloatingPoint() {
    // Test doubles
    double a = 3.14, b = 2.718;
    double origA = a, origB = b;
    swap(a, b);
    verifySwap(origA, origB, a, b, "Double swap failed");

    // Test floats
    float af = 1.1f, bf = 2.2f;
    float origAf = af, origBf = bf;
    swap(af, bf);
    verifySwap(origAf, origBf, af, bf, "Float swap failed");
}

void testCharacters() {
    char a = 'a', b = 'b';
    char origA = a, origB = b;
    swap(a, b);
    verifySwap(origA, origB, a, b, "Character swap failed");
}

void testStrings() {
    // Test regular strings
    std::string a = "hello", b = "world";
    std::string origA = a, origB = b;
    swap(a, b);
    verifySwap(origA, origB, a, b, "String swap failed");

    // Verify string capacity is properly handled
    std::string longStr(1000, 'x');
    std::string shortStr = "short";
    swap(longStr, shortStr);
    assert(shortStr.length() == 1000 && "String capacity swap failed");
    assert(longStr == "short");
    assert(shortStr[0] == 'x');
}

void testVectors() {
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {4, 5, 6, 7};
    std::vector<int> origA = a, origB = b;
    swap(a, b);
    verifySwap(origA, origB, a, b, "Vector swap failed");
}

void testCustomClass() {
    TestClass a(42), b(123);
    TestClass origA = a, origB = b;
    swap(a, b);
    verifySwap(origA, origB, a, b, "Custom class swap failed");
}

void testSameAddressProtection() {
    // Test with various types
    int a = 5;
    swap(a, a);
    assert(a == 5 && "Self-swap corrupted integer value");

    std::string str = "test";
    swap(str, str);
    assert(str == "test" && "Self-swap corrupted string value");

    std::vector<int> vec = {1, 2, 3};
    swap(vec, vec);
    assert(vec.size() == 3 && vec[0] == 1 && "Self-swap corrupted vector");
}

void testLargeStrings() {
    std::string a(1000000, 'a'); // 1MB string
    std::string b(2000000, 'b'); // 2MB string
    size_t originalSizeA = a.size();
    size_t originalSizeB = b.size();
    swap(a, b);
    assert(a.size() == originalSizeB && b.size() == originalSizeA &&
           "Large string swap failed");
    assert(a[0] == 'b');
    assert(b[0] == 'a');
}

void testEmptyContainers() {
    // Empty string
    std::string a = "", b = "hello";
    std::string origA = a, origB = b;
    swap(a, b);
    verifySwap(origA, origB, a, b, "Empty string swap failed");

    // Empty vector
    std::vector<int> va, vb = {1, 2, 3};
    std::vector<int> origVa = va, origVb = vb;
    swap(va, vb);
    verifySwap(origVa, origVb, va, vb, "Empty vector swap failed");
}
