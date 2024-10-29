/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 17:38:27 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/29 18:48:35 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/easyfind.hpp"

void simple_test() {
    std::list<int> testList = {1, 500, 28, 33, 21, 434, 235, 787, 123432};

    try {
        easyfind(testList, 787);
    } catch (std::invalid_argument &e) {
        assert(false && "Target should be find, so something whent wrong\n");
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
}

int main() {
    simple_test();
    return 0;
}
