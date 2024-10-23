/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_iter.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/23 21:43:33 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/23 21:43:33 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.hpp"
#include <stdexcept>

void incrementInt(int &n) { n++; }
void multiplyByTwo(double &n) { n *= 2; }
void toUpperCase(char &c) { c = std::toupper(c); }
void throwingFunction(int & /*n*/) {
    throw std::runtime_error("Test exception");
}
void modifySafeStruct(SafeTestStruct &ts) {
    if (ts.value != 0) { // Safe check
        ts.value *= 2;
    }
}

void modifyTestStruct(TestStruct &ts) { ts.value *= 2; }

void testIntegerArray() {
    std::cout << "Testing integer array..." << '\n';
    std::cout.flush();

    int arr[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    iter(arr, size, incrementInt);

    // Verify each element was incremented
    assert(arr[0] == 2 && "First element not incremented");
    assert(arr[1] == 3 && "Second element not incremented");
    assert(arr[2] == 4 && "Third element not incremented");
    assert(arr[3] == 5 && "Fourth element not incremented");
    assert(arr[4] == 6 && "Fifth element not incremented");
    std::cout.flush();
}

void testDoubleArray() {
    std::cout << "Testing double array..." << '\n';

    double arr[] = {1.5, 2.5, 3.5};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    iter(arr, size, multiplyByTwo);

    // Verify each element was multiplied by 2
    assert(arr[0] == 3.0 && "First element not multiplied");
    assert(arr[1] == 5.0 && "Second element not multiplied");
    assert(arr[2] == 7.0 && "Third element not multiplied");
    std::cout.flush();
}

void testCharArray() {
    std::cout << "Testing char array..." << '\n';

    char arr[] = {'a', 'b', 'c', 'd'};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    iter(arr, size, toUpperCase);

    // Verify each character was converted to uppercase
    assert(arr[0] == 'A' && "First char not uppercase");
    assert(arr[1] == 'B' && "Second char not uppercase");
    assert(arr[2] == 'C' && "Third char not uppercase");
    assert(arr[3] == 'D' && "Fourth char not uppercase");
    std::cout.flush();
}

void testCStyleString() {
    std::cout << "Testing C-style string..." << '\n';

    char str[] = "hello";
    size_t size = strlen(str) + 1; // Include null terminator

    iter(str, size, toUpperCase);

    // Verify string was converted to uppercase and stopped at null terminator
    assert(strcmp(str, "HELLO") == 0 && "String not properly converted");
    std::cout.flush();
}

void testNullptr() {
    std::cout << "Testing nullptr handling..." << '\n';

    int *arr = nullptr;
    bool exceptionCaught = false;

    try {
        iter(arr, 5, incrementInt);
    } catch (const std::invalid_argument &e) {
        exceptionCaught = true;
        assert(std::string(e.what()) == "T1 can not be a nullptr\n");
    }

    assert(exceptionCaught && "nullptr not properly handled");
    std::cout.flush();
}

void testZeroSize() {
    std::cout << "Testing zero size handling..." << '\n';

    int arr[] = {1, 2, 3};
    bool exceptionCaught = false;

    try {
        iter(arr, 0, incrementInt);
    } catch (const std::invalid_argument &e) {
        exceptionCaught = true;
        assert(std::string(e.what()) == "T2 must be more then 0\n");
    }

    assert(exceptionCaught && "Zero size not properly handled");
    std::cout.flush();
}

void testEmptyArray() {
    std::cout << "Testing empty array..." << '\n';

    char arr[] = {'\0'};
    bool functionCalled = false;

    auto testFunc = [&functionCalled](char & /*c*/) { functionCalled = true; };
    try {
        iter(arr, 0, testFunc);
    } catch (std::invalid_argument &e) {
        static_assert(true, "");
    }

    assert(!functionCalled && "Function should not be called for empty array");
    std::cout.flush();
}

void testCustomType() {
    std::cout << "Testing custom type..." << '\n';

    TestStruct arr[] = {{1}, {2}, {3}};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    iter(arr, size, modifyTestStruct);

    assert(arr[0].value == 2 && "First custom element not modified");
    assert(arr[1].value == 4 && "Second custom element not modified");
    assert(arr[2].value == 6 && "Third custom element not modified");
    std::cout.flush();
}

void testExceptionPropagation() {
    std::cout << "Testing exception propagation..." << '\n';

    int arr[] = {1, 2, 3};
    bool exceptionCaught = false;

    try {
        iter(arr, 3, throwingFunction);
    } catch (const std::runtime_error &e) {
        exceptionCaught = true;
        assert(std::string(e.what()) == "Test exception");
    }

    assert(exceptionCaught && "Exception not properly propagated");
    std::cout.flush();
}

void testLargeArray() {
    std::cout << "Testing large array..." << '\n';

    const size_t size = 1000000;
    int *arr = new int[size];

    // Initialize and print initial values
    for (size_t i = 0; i < size; i++) {
        arr[i] = i;
    }

    iter(arr, size, incrementInt);

    // Verify random samples
    assert(arr[0] == 1 && "First element of large array not incremented");
    assert(arr[size / 2] == size / 2 + 1 &&
           "Middle element of large array not incremented");
    assert(arr[size - 1] == size &&
           "Last element of large array not incremented");

    delete[] arr;
    std::cout.flush();
}

void testMultipleFunctionTypes() {
    std::cout << "Testing multiple function types..." << '\n';

    // Test with regular function
    char arr1[] = {'a', 'b', '\0'};
    iter(arr1, 3, toUpperCase);
    assert(arr1[0] == 'A' && arr1[1] == 'B');

    // Test with lambda
    char arr2[] = {'a', 'b', '\0'};
    iter(arr2, 3, [](char &c) {
        if (c != '\0')
            c = std::toupper(c);
    });
    assert(arr2[0] == 'A' && arr2[1] == 'B');

    // Test with std::function
    char arr3[] = {'a', 'b', '\0'};
    std::function<void(char &)> func = [](char &c) {
        if (c != '\0')
            c = std::toupper(c);
    };
    iter(arr3, 3, func);
    assert(arr3[0] == 'A' && arr3[1] == 'B');
    std::cout.flush();
}

void testOversizedIntArray() {
    std::cout << "Testing oversized int array..." << '\n';

    int arr[] = {1, 2, 3}; // Array of size 3
    const size_t actual_size = sizeof(arr) / sizeof(arr[0]);
    const size_t oversized = actual_size + 5; // Using size bigger than array

    std::cout << "Warning: The following test may cause undefined behavior"
              << '\n';
    std::cout << "Actual array size: " << actual_size
              << ", Testing with size: " << oversized << '\n';

    // Store original values for comparison
    int original[] = {1, 2, 3};

    bool undefined_behavior_detected = false;
    try {
        iter(arr, oversized, incrementInt);

        // Check if any unexpected modifications occurred
        for (size_t i = 0; i < actual_size; i++) {
            if (arr[i] != original[i] + 1) {
                undefined_behavior_detected = true;
            }
        }
    } catch (...) {
        undefined_behavior_detected = true;
    }

    std::cout << "Oversized int array test completed" << '\n';
    if (undefined_behavior_detected) {
        std::cout << "Warning: Undefined behavior detected with oversized array"
                  << '\n';
    }
    std::cout.flush();
}

void testOversizedCharArray() {
    std::cout << "Testing oversized char array..." << '\n';

    char arr[] = {'a', 'b', 'c'}; // Array of size 3
    const size_t actual_size = sizeof(arr) / sizeof(arr[0]);
    const size_t oversized = actual_size + 5;

    std::cout << "Warning: The following test may cause undefined behavior"
              << '\n';
    std::cout << "Actual array size: " << actual_size
              << ", Testing with size: " << oversized << '\n';

    char original[] = {'a', 'b', 'c'};

    bool undefined_behavior_detected = false;
    try {
        iter(arr, oversized, toUpperCase);

        // Check if any unexpected modifications occurred
        for (size_t i = 0; i < actual_size; i++) {
            if (std::toupper(original[i]) != arr[i]) {
                undefined_behavior_detected = true;
            }
        }
    } catch (...) {
        undefined_behavior_detected = true;
    }

    std::cout << "Oversized char array test completed" << '\n';
    if (undefined_behavior_detected) {
        std::cout
            << "Warning: Undefined behavior detected with oversized char array"
            << '\n';
    }
    std::cout.flush();
}

void testOversizedCString() {
    std::cout << "Testing oversized C-string..." << '\n';

    char str[] = "hello"; // Array of size 6 (including null terminator)
    const size_t actual_size = strlen(str);
    const size_t oversized = actual_size + 5;

    std::cout << "Actual string length: " << actual_size
              << ", Testing with size: " << oversized << '\n';

    // This should safely stop at null terminator despite oversized length
    iter(str, oversized, toUpperCase);

    // Verify only the actual string was modified
    assert(strcmp(str, "HELLO") == 0 &&
           "C-string not properly handled with oversized length");
    std::cout.flush();
}

void testOversizedWithNullTerminator() {
    std::cout << "Testing oversized array with null terminator..." << '\n';

    char arr[] = {'a', 'b', '\0', 'c',
                  'd'}; // Array with null terminator in middle
    const size_t actual_size = sizeof(arr) / sizeof(arr[0]);
    const size_t oversized = actual_size + 5;

    iter(arr, oversized, toUpperCase);

    // Verify only elements before null terminator were modified
    assert(arr[0] == 'A' && "First element not modified");
    assert(arr[1] == 'B' && "Second element not modified");
    assert(arr[2] == '\0' && "Null terminator modified");
    assert(arr[3] == 'C' && "Element after null terminator is not modified");
    assert(arr[4] == 'D' && "Last element is not modified");
    std::cout.flush();
}

void testOversizedCustomType() {
    std::cout << "Testing oversized custom type array..." << '\n';

    SafeTestStruct arr[] = {{1}, {2}, {0}, {4}}; // Array with "null" in middle
    const size_t actual_size = sizeof(arr) / sizeof(arr[0]);
    const size_t oversized = actual_size + 5;

    std::cout << "Warning: The following test may cause undefined behavior"
              << '\n';
    std::cout << "Actual array size: " << actual_size
              << ", Testing with size: " << oversized << '\n';

    bool undefined_behavior_detected = false;
    try {
        iter(arr, oversized, modifySafeStruct);
        assert(arr[0].value == 2 && "First element not properly modified");
        assert(arr[1].value == 4 && "Second element not properly modified");
        assert(arr[2].value == 0 && "Null element modified");
        assert(arr[3].value == 8 && "Element after null not modified");
    } catch (std::exception &e) {
        undefined_behavior_detected = true;
    }

    std::cout << "Oversized custom type array test completed" << '\n';
    if (undefined_behavior_detected) {
        std::cout << "Warning: Undefined behavior detected with oversized "
                     "custom type array"
                  << '\n';
    }
    std::cout.flush();
}
