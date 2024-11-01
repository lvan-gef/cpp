/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   span_test.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 18:44:52 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/29 18:44:55 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.hpp"

std::vector<int> randomVector(unsigned int N) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(std::numeric_limits<int>::min(),
                                        std::numeric_limits<int>::max());

    std::vector<int> tmp;
    tmp.reserve(N);

    while (tmp.size() < N) {
        tmp.push_back(dis(gen));
    }

    return tmp;
}