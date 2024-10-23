#include "../include/tester.hpp"

static void testDefaultConstructor() {
    std::cout << "Testing default constructor..." << '\n';
    Array<int> arr;
    assert(arr.size() == 0 && "Default constructor should create empty array");
}

static void testSizeConstructor() {
    std::cout << "Testing size constructor..." << '\n';
    Array<int> arr(5);
    assert(arr.size() == 5 &&
           "Size constructor should create array of correct size");

    // Test zero size
    Array<int> zeroArr(0);
    assert(zeroArr.size() == 0 &&
           "Size constructor with 0 should create empty array");
}

static void testCopyConstructor() {
    std::cout << "Testing copy constructor..." << std::endl;
    Array<int> arr1(3);
    arr1[0] = 1;
    arr1[1] = 2;
    arr1[2] = 3;

    Array<int> arr2(arr1);
    assert(arr2.size() == arr1.size() && "Copy constructor should preserve size");
    assert(arr2[0] == 1 && "Copy constructor should copy first element");
    assert(arr2[1] == 2 && "Copy constructor should copy middle element");
    assert(arr2[2] == 3 && "Copy constructor should copy last element");

    // Modify copy to ensure deep copy
    arr2[0] = 10;
    assert(arr1[0] == 1 &&
           "Original array should not be affected by changes to copy");

    arr1[1] = 20;
    assert(arr2[1] == 2 &&
           "Copy array should not be affected by changes to original");
}

static void testAssignmentOperator() {
    std::cout << "Testing assignment operator..." << '\n';
    size_t len = 3;
    Array<int> arr1(len);
    arr1[0] = 1;
    arr1[1] = 2;
    arr1[2] = 3;

    Array<int> arr2 = arr1;
    assert(arr2.size() == len && "Assignment should preserve size");
    assert(arr2[0] == 1 && "Assignment should copy first element");
    assert(arr2[1] == 2 && "Assignment should copy middle element");
    assert(arr2[2] == 3 && "Assignment should copy last element");

    // Self assignment
    arr1 = arr1;
    assert(arr1.size() == len && "Self assignment should work");
    assert(arr1[0] == 1 && "Self assignment should preserve data");
    assert(arr1[1] == 2 && "Self assignment should preserve data");
    assert(arr1[2] == 3 && "Self assignment should preserve data");


    // Modify copy to ensure deep copy
    arr2[0] = 10;
    assert(arr1[0] == 1 &&
           "Original array should not be affected by changes to copy");

    arr1[1] = 20;
    assert(arr2[1] == 2 &&
           "Copy array should not be affected by changes to original");
}

static void testMoveConstructor() {
    std::cout << "Testing move constructor..." << '\n';
    Array<int> arr1(3);
    arr1[0] = 1;
    arr1[1] = 2;
    arr1[2] = 3;

    Array<int> arr2(std::move(arr1));
    assert(arr2.size() == 3 && "Move constructor should preserve size");
    assert(arr2[0] == 1 && "Move constructor should preserve first element");
    assert(arr2[1] == 2 && "Move constructor should preserve middle element");
    assert(arr2[2] == 3 && "Move constructor should preserve last element");
    assert(arr1.size() == 0 && "Moved-from array should be empty");
}

static void testDifferentTypes() {
    std::cout << "Testing different types..." << '\n';

    // Test with strings
    Array<std::string> strArr(2);
    strArr[0] = "Hello";
    strArr[1] = "World";
    assert(strArr[0] == "Hello" &&
           "String array should store strings correctly");
    assert(strArr[1] == "World" &&
           "String array should store multiple strings");

    // Test with vectors
    Array<std::vector<int>> vecArr(2);
    vecArr[0] = std::vector<int>{1, 2, 3};
    vecArr[1] = std::vector<int>{4, 5, 6};
    assert(vecArr[0].size() == 3 &&
           "Vector array should store vectors correctly");
    assert(vecArr[0][0] == 1 && "Vector elements should be accessible");
}

static void testSubscriptOperator() {
    std::cout << "Testing subscript operator..." << '\n';
    Array<int> arr(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;

    // Test valid access
    assert(arr[0] == 1 && "Subscript operator should access first element");
    assert(arr[1] == 2 && "Subscript operator should access middle element");
    assert(arr[2] == 3 && "Subscript operator should access last element");

    // Test const access
    const Array<int> &constArr = arr;
    assert(constArr[0] == 1 && "Const subscript operator should work");

    // Test invalid access
    bool caught = false;
    try {
        arr[3] = 4; // Should throw
    } catch (const std::out_of_range &) {
        caught = true;
    }
    assert(caught && "Out of bounds access should throw exception");
}

bool array_test() {
    try {
        testDefaultConstructor();
        testSizeConstructor();
        testCopyConstructor();
        testAssignmentOperator();
        testMoveConstructor(); // here
        testDifferentTypes();
        testSubscriptOperator();
        std::cout << "All tests passed successfully!" << '\n';
    } catch (const std::exception &e) {
        std::cerr << "Test failed with exception: " << e.what() << '\n';
        return false;
    }

    return true;
}
