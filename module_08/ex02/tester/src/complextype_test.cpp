/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   complextype_test.cpp                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/01 17:58:33 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/11/02 00:41:04 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.hpp"

static void vectorTest() {
    MutantStack<std::vector<int>> ms_vec;
    std::stack<std::vector<int>> og_vec;

    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> v2 = {4, 5, 6};

    assert(ms_vec.empty() == true && "ms_vec should be empty");
    ms_vec.push(v1);
    ms_vec.push(v2);
    assert(ms_vec.empty() != true && "ms_vec should not be empty");
    assert(ms_vec.size() == 2 && "ms_vec should be size 2");
    assert(ms_vec.top() == v2 && "ms_vec should be {4, 5, 6}");

    assert(og_vec.empty() == true && "og_vec should be empty");
    og_vec.push(v1);
    og_vec.push(v2);
    assert(og_vec.empty() != true && "og_vec should not be empty");
    assert(og_vec.size() == 2 && "og_vec should be size 2");
    assert(og_vec.top() == v2 && "og_vec should be {4, 5, 6}");

    assert(ms_vec.size() == og_vec.size() &&
           "Own and Og should be the same size: 2");
    assert(ms_vec.top() == og_vec.top() &&
           "Own and Og should be the seem: {4, 5, 6}");

    ms_vec.pop();
    assert(ms_vec.empty() != true && "ms_vec should not be empty");
    assert(ms_vec.size() == 1 && "ms_vec should be size 1");
    assert(ms_vec.top() == v1 && "ms_vec should be {1, 2, 3}");

    og_vec.pop();
    assert(og_vec.empty() != true && "og_vec should not be empty");
    assert(og_vec.size() == 1 && "og_vec should be size 1");
    assert(og_vec.top() == v1 && "og_vec should be {1, 2, 3}");

    assert(ms_vec.size() == og_vec.size() &&
           "Own and Og should be the same size: 1");
    assert(ms_vec.top() == og_vec.top() &&
           "Own and Og should be the seem: {1, 2, 3}");

    ms_vec.pop();
    assert(ms_vec.empty() == true && "ms_vec should be empty");

    og_vec.pop();
    assert(og_vec.empty() == true && "og_vec should be empty");
}

void testComplexTypes() {
    std::cout << "Start ComplexType Operations Test" << '\n';

    MutantStack<ComplexType> ms_complex;
    std::stack<ComplexType> og_complex;

    std::vector<int> expected = {1, 2, 3};
    ComplexType ct1 = ComplexType("first", {1, 2, 3});
    ComplexType ct2 = ComplexType("second", {1, 2, 3});

    assert(ms_complex.empty() == true && "ms_complex should be empty");
    ms_complex.push(ct1);
    ms_complex.push(ct2);
    assert(ms_complex.empty() != true && "ms_complex should not be empty");
    assert(ms_complex.size() == 2 && "ms_complex should be size 2");
    assert(ms_complex.top() == ct2 && "ms_complex should be {4, 5, 6}");

    assert(og_complex.empty() == true && "og_complex should be empty");
    og_complex.push(ct1);
    og_complex.push(ct2);
    assert(og_complex.empty() != true && "og_complex should not be empty");
    assert(og_complex.size() == 2 && "og_complex should be size 2");
    assert(og_complex.top() == ct2 && "og_complex should be {4, 5, 6}");

    assert(og_complex.size() == og_complex.size() &&
           "Own and Og should be the same size: 2");
    assert(og_complex.top() == og_complex.top() &&
           "Own and Og should be the seem: second, {4, 5, 6}");

    assert(ms_complex.top().name == "second" && "Expect name to be 'second'");
    assert(ms_complex.top().data == expected && "Expect data to be {1, 2, 3}");

    assert(og_complex.top().name == "second" && "Expect name to be 'second'");
    assert(og_complex.top().data == expected && "Expect data to be {1, 2, 3}");

    ms_complex.pop();
    assert(ms_complex.size() == 1 && "Expect that ms_complex.size() == 1");

    og_complex.pop();
    assert(og_complex.size() == 1 && "Expect that og_complex.size() == 1");

    assert(ms_complex.size() == og_complex.size() &&
           "Own and Og should be the same size: 1");
    assert(ms_complex.top() == og_complex.top() &&
           "Own and Og should be the seem: first, {1, 2, 3}");

    assert(ms_complex.top().name == "first" && "Expect name to be 'first'");
    assert(ms_complex.top().data == expected && "Expect data to be {1, 2, 3}");

    assert(og_complex.top().name == "first" && "Expect name to be 'first'");
    assert(og_complex.top().data == expected && "Expect data to be {1, 2, 3}");

    ms_complex.pop();
    assert(ms_complex.size() == 0 && "Expect that ms_complex.size() == 0");

    og_complex.pop();
    assert(og_complex.size() == 0 && "Expect that og_complex.size() == 0");

    vectorTest();

    std::cout << "End ComplexType Operations Test" << '\n' << '\n';
}
