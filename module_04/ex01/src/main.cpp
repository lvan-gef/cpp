/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:33:41 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:33:41 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Animal.hpp"
#include "../include/Cat.hpp"
#include "../include/Dog.hpp"
#include "../include/WrongAnimal.hpp"
#include "../include/WrongCat.hpp"
#include <new>

void subject_tester() {
    const Animal *j = new Dog();
    std::cout << '\n';
    const Animal *i = new Cat();
    std::cout << '\n';
    delete j; // should not create a leak
    std::cout << '\n';
    delete i;
    std::cout << '\n';

    const size_t len = 10;
    Animal *animal[len] = {};

    for (size_t index = 0; index < len; ++index) {
        try {
            if (index % 2) {
                animal[index] = new Cat();
            } else {
                animal[index] = new Dog();
            }
            std::cout << '\n';

        } catch (std::bad_alloc &) {
            for (size_t indx = 0; indx < index; ++indx) {
                delete animal[indx];
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
