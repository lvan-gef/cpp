/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Cat.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:33:04 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:33:04 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cat.hpp"

Cat::Cat() : Animal("Cat") {
    std::cout << "Default constructor for Cat is called" << '\n';
}

Cat::Cat(const Cat &rhs) : Animal(rhs) {
    std::cout << "Default copy constructor for Cat is called" << '\n';
}

Cat &Cat::operator=(const Cat &rhs) {
    std::cout << "Copy assignment constructor for Cat is called" << '\n';

    if (this != &rhs) {
        Animal::operator=(rhs);
    }

    return *this;
}

Cat::Cat(Cat &&rhs) noexcept : Animal(std::move(rhs)) {
    std::cout << "Default move constructor for Cat is called" << '\n';
}

Cat &Cat::operator=(Cat &&rhs) noexcept {
    std::cout << "Move assignment operator for Cat is called" << '\n';

    if (this != &rhs) {
        Animal::operator=(std::move(rhs));
    }

    return *this;
}

void Cat::makeSound() const { std::cout << "meauw meauw" << '\n'; }

Cat::~Cat() { std::cout << "Default destructor for Cat is called" << '\n'; }
