/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   easyfind_test.cpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 17:42:40 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/11/02 20:11:18 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.hpp"

void testVector() {
    std::cout << "Running test: " << "vector" << '\n';

    std::vector<int> vec = {1, 2, 3, 4, 5};
    runTest(vec, 3, true);
    runTest(vec, 10, false);
    runTest(vec, 1, true);
    runTest(vec, 5, true);

    std::cout << "Pass test: " << "vector" << '\n' << '\n';
}

void testList() {
    std::cout << "Running test: " << "list" << '\n';

    std::list<int> lst = {10, 20, 30, 40, 50};
    runTest(lst, 30, true);
    runTest(lst, 25, false);
    runTest(lst, 10, true);
    runTest(lst, 50, true);

    std::cout << "Pass test: " << "list" << '\n' << '\n';
}

void testDeque() {
    std::cout << "Running test: " << "deque" << '\n';

    std::deque<int> deq = {100, 200, 300};
    runTest(deq, 200, true);
    runTest(deq, 150, false);
    runTest(deq, 100, true);
    runTest(deq, 300, true);

    std::cout << "Pass test: " << "deque" << '\n' << '\n';
}

void testSet() {
    std::cout << "Running test: " << "set" << '\n';

    std::set<int> set = {1, 3, 5, 7, 9};
    runTest(set, 5, true);
    runTest(set, 4, false);
    runTest(set, 1, true);
    runTest(set, 9, true);

    std::cout << "Pass test: " << "set" << '\n' << '\n';
}

void testEdgeCases() {
    std::cout << "Running test: " << "empty vector" << '\n';
    std::vector<int> empty;
    runTest(empty, 1, false);
    std::cout << "Pass test: " << "empty vector" << '\n' << '\n';

    std::cout << "Running test: " << "empty list" << '\n';
    std::list<int> emptyList;
    runTest(emptyList, 1, false);
    std::cout << "Pass test: " << "empty list" << '\n' << '\n';

    std::cout << "Running test: " << "empty deque" << '\n';
    std::deque<int> emptyDeque;
    runTest(emptyDeque, 1, false);
    std::cout << "Pass test: " << "empty deque" << '\n' << '\n';

    std::cout << "Running test: " << "empty set" << '\n';
    std::set<int> emptySet;
    runTest(emptyDeque, 1, false);
    std::cout << "Pass test: " << "empty set" << '\n' << '\n';

    std::cout << "Running test: " << "single element" << '\n';
    std::vector<int> single = {42};
    runTest(single, 42, true);
    runTest(single, 43, false);
    std::cout << "Pass test: " << "single element" << '\n' << '\n';

    std::cout << "Running test: " << "duplicate elements" << '\n';
    std::vector<int> duplicates = {1, 2, 2, 2, 3};
    runTest(duplicates, 2, true);
    std::cout << "Pass test: " << "duplicate elements" << '\n' << '\n';

    std::cout << "Running test: " << "negative elements" << '\n';
    std::vector<int> negatives = {-3, -2, -1, 0, 1};
    runTest(negatives, -2, true);
    std::cout << "Pass test: " << "negative elements" << '\n' << '\n';
}

void runAllTests() {
    std::cout << "Starting easyfind template tests\n" << '\n';

    testVector();
    testList();
    testDeque();
    testSet();
    testEdgeCases();

    std::cout << "\nAll tests completed successfully!" << '\n';
}

int testEasyFind() {
    try {
        runAllTests();
    } catch (const std::exception &e) {
        std::cerr << "Test suite failed: " << e.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "Test suite failed with unknown exception" << '\n';
        return 1;
    }
    return 0;
}
