/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/23 21:43:47 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/23 21:43:47 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../tester/include/tester.hpp"
#include "../include/Array.hpp"

#define MAX_VAL 750

bool subject_cpp() {
    Array<int> numbers(MAX_VAL);
    std::cout << numbers.size() << '\n';
    int *mirror = new int[MAX_VAL];
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++) {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }

    Array<int> tmp = numbers;
    Array<int> test(tmp);
    for (int i = 0; i < MAX_VAL; i++) {
        if (mirror[i] != numbers[i]) {
            std::cerr << "didn't save the same value!!" << std::endl;
            return false;
        }
    }

    try {
        numbers[-2] = 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    try {
        numbers[MAX_VAL] = 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }

    for (int i = 0; i < MAX_VAL; i++) {
        numbers[i] = rand();
    }

    delete[] mirror;
    return true;
}
int main(int, char **) {
    subject_cpp();
    array_test();
    return 0;
}
