/* ************************************************************************** */
/*                                                                            */
/*   main.cpp                                           :+:    :+:            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Updated: 2024/11/02 01:48:39 by lvan-gef      ########   odam.nl         */
/*   Updated: 2024/11/02 01:50:25 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/easyfind.hpp"

static void simple_test() {
    std::cout << "Start simple easyfind test" << '\n';

    std::list<int> testList = {1, 500, 28, 33, 21, 434, 235, 787, 123432};

    try {
        easyfind(testList, 787);
    } catch (std::invalid_argument &e) {
        assert(false && "Target should be find, so something whent wrong\n");
    } catch (...) {
        assert(false && "Unknow error should not be here\n");
    }

    try {
        easyfind(testList, 0);
        assert(false && "Should throw a error, so something whent wrong\n");
    } catch (std::invalid_argument &e) {
        static_assert(true, "Succesfull throw a error ");
    } catch (...) {
        assert(false && "Unknow error should not be here\n");
    }

    std::vector<int> bigVector;
    bigVector.reserve(100000);
    for (int index = 0; index < 100000; index++) {
        bigVector.push_back(index);
    }

    try {
        easyfind(bigVector, 99999);
    } catch (std::invalid_argument &e) {
        assert(false && "Target should be find, so something whent wrong\n");
    } catch (...) {
        assert(false && "Unknow error should not be here\n");
    }

    try {
        easyfind(testList, 100000);
        assert(false && "Should throw a error, so something whent wrong\n");
    } catch (std::invalid_argument &e) {
        static_assert(true, "Succesfull throw a error ");
    } catch (...) {
        assert(false && "Unknow error should not be here\n");
    }

    std::cout << "End simple easyfind test" << '\n' << '\n';
}

int main() {
    simple_test();

    return 0;
}
