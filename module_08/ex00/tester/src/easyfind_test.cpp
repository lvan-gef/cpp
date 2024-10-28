/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   easyfind_test.cpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 17:42:40 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/28 17:42:43 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.hpp"

// Helper function to run a test case and report results
template <typename T>
void runTest(T container, int target, bool shouldSucceed) {
    try {
        easyfind(container, target);
        if (shouldSucceed) {
            std::cout << "✓ Test passed: Found target " << target << std::endl;
        } else {
            std::cout << "✗ Test failed: Expected exception but found target"
                      << std::endl;
            assert(false);
        }
    } catch (const std::invalid_argument &e) {
        if (!shouldSucceed) {
            std::cout
                << "✓ Test passed: Correctly throw exception for missing target"
                << std::endl;
        } else {
            std::cout << "✗ Test failed: Unexpected exception - " << e.what()
                      << std::endl;
            assert(false);
        }
    } catch (...) {
        std::cout << "✗ Test failed: Unexpected exception type" << std::endl;
        assert(false);
    }
}

// Test suite
void runAllTests() {
    std::cout << "Starting easyfind template tests\n" << std::endl;

    // Test with vector
    std::cout << "Running test: " << "vector" << std::endl;
    std::vector<int> vec = {1, 2, 3, 4, 5};
    runTest(vec, 3, true);
    runTest(vec, 10, false);
    runTest(vec, 1, true);
    runTest(vec, 5, true);

    // Test with list
    std::cout << "Running test: " << "list" << std::endl;
    std::list<int> lst = {10, 20, 30, 40, 50};
    runTest(lst, 30, true);
    runTest(lst, 25, false);
    runTest(lst, 10, true);
    runTest(lst, 50, true);

    // Test with deque
    std::cout << "Running test: " << "deque" << std::endl;
    std::deque<int> deq = {100, 200, 300};
    runTest(deq, 200, true);
    runTest(deq, 150, false);
    runTest(deq, 100, true);
    runTest(deq, 300, true);

    // Test with set
    std::cout << "Running test: " << "set" << std::endl;
    std::set<int> set = {1, 3, 5, 7, 9};
    runTest(set, 5, true);
    runTest(set, 4, false);
    runTest(set, 1, true);
    runTest(set, 9, true);

    // Test edge cases
    std::cout << "Running test: " << "empty vector" << std::endl;
    std::vector<int> empty;
    runTest(empty, 1, false);

    std::cout << "Running test: " << "empty list" << std::endl;
    std::list<int> emptyList;
    runTest(emptyList, 1, false);

    std::cout << "Running test: " << "empty deque" << std::endl;
    std::deque<int> emptyDeque;
    runTest(emptyDeque, 1, false);

    std::cout << "Running test: " << "empty set" << std::endl;
    std::set<int> emptySet;
    runTest(emptyDeque, 1, false);

    std::cout << "Running test: " << "single element" << std::endl;
    std::vector<int> single = {42};
    runTest(single, 42, true);
    runTest(single, 43, false);

    std::cout << "Running test: " << "duplicate elements" << std::endl;
    std::vector<int> duplicates = {1, 2, 2, 2, 3};
    runTest(duplicates, 2, true);

    std::cout << "Running test: " << "negative elements" << std::endl;
    std::vector<int> negatives = {-3, -2, -1, 0, 1};
    runTest(negatives, -2, true);

    std::cout << "\nAll tests completed successfully!" << std::endl;
}

int testEasyFind() {
    try {
        runAllTests();
    } catch (const std::exception &e) {
        std::cerr << "Test suite failed: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Test suite failed with unknown exception" << std::endl;
        return 1;
    }
    return 0;
}
