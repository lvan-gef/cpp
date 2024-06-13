/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Dog.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:33:04 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:33:04 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Dog.hpp"

Dog::Dog() : Animal("Dog") {
    std::cout << "Default constructor for Dog is called" << '\n';
}

Dog::Dog(const Dog &rhs) : Animal(rhs) {
    std::cout << "Default copy constructor for Dog is called" << '\n';
}

Dog &Dog::operator=(const Dog &rhs) {
    std::cout << "Copy assignment constructor for Dog is called" << '\n';

    if (this != &rhs) {
        Animal::operator=(rhs);
    }

    return *this;
}

Dog::Dog(Dog &&rhs) noexcept : Animal(std::move(rhs)) {
    std::cout << "Default move constructor for Dog is called" << '\n';
}

Dog &Dog::operator=(Dog &&rhs) noexcept {
    std::cout << "Move assignment operator for Dog is called" << '\n';

    if (this != &rhs) {
        Animal::operator=(std::move(rhs));
    }

    return *this;
}

void Dog::makeSound() const { std::cout << "woef woef" << '\n'; }

Dog::~Dog() { std::cout << "Default destructor for Dog is called" << '\n'; }
