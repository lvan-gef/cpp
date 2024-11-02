/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   span_test.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 18:44:52 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/11/02 20:15:53 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.hpp"

void printer(std::vector<int> data) {
    for (int nbr : data) {
        std::cerr << nbr << '\n';
    }
}

std::vector<int> randomVector(unsigned int N) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(std::numeric_limits<int>::min(),
                                        std::numeric_limits<int>::max());

    std::vector<int> tmp;
    tmp.reserve(N);

    auto start = std::chrono::high_resolution_clock::now();
    while (tmp.size() < N) {
        tmp.push_back(dis(gen));
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Create random data<" << N
              << "> duration: " << duration.count() << " milliseconds"
              << std::endl;

    start = std::chrono::high_resolution_clock::now();
    printer(tmp);
    end = std::chrono::high_resolution_clock::now();
    duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Print         data<" << N
              << "> duration: " << duration.count() << " milliseconds"
              << std::endl;

    return tmp;
}
