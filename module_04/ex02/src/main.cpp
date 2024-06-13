/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:34:28 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:34:28 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cat.hpp"
#include "../include/Dog.hpp"
#include <cstdlib>
#include <iostream>
#include <new>

void subject_tester() {
    const AAnimal *j = new Dog();
    std::cout << '\n';
    const AAnimal *i = new Cat();
    std::cout << '\n';
    delete j; // should not create a leak
    std::cout << '\n';
    delete i;
    std::cout << '\n';

    const size_t len = 10;
    AAnimal *animal[len] = {};

    for (size_t index = 0; index < len; ++index) {
        try {
            if (index % 2) {
                animal[index] = new Cat();
            } else {
                animal[index] = new Dog();
            }
            std::cout << '\n';

        } catch (std::bad_alloc &) {
            for (auto &indx : animal) {
                delete indx;
            }
            throw;
        }
    }

    for (auto &index : animal) {
        std::cout << "Animal type: " << index->getType()
                  << " Making sounds like this: ";
        index->makeSound();
    }

    std::cout << '\n';
    for (auto &index : animal) {
        delete index;
        std::cout << '\n';
    }
}

int main() {
    subject_tester();

    return 0;
}
