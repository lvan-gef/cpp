/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Animal.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:33:04 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:33:04 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Animal.hpp"

Animal::Animal() : type_("Animal") {
    std::cout << "Default constructor for Animal is called" << '\n';
}

Animal::Animal(std::string name) : type_(std::move(name)) {
    std::cout << "Named constructor for Animal is called" << '\n';
}

Animal::Animal(const Animal &rhs) : type_(rhs.type_) {
    std::cout << "Default copy constructor for Animal is called" << '\n';
}

Animal &Animal::operator=(const Animal &rhs) {
    std::cout << "Copy assignment constructor for Animal is called" << '\n';

    if (this != &rhs) {
        type_ = rhs.type_;
    }

    return *this;
}

Animal::Animal(Animal &&rhs) noexcept : type_(std::move(rhs.type_)) {
    std::cout << "Default move constructor for Animal is called" << '\n';
    rhs.type_.clear();
}

Animal &Animal::operator=(Animal &&rhs) noexcept {
    std::cout << "Move assignment operator for Animal is called" << '\n';

    if (this != &rhs) {
        type_ = std::move(rhs.type_);
        rhs.type_.clear();
    }

    return *this;
}

std::string Animal::getType() const { return this->type_; }

void Animal::makeSound() const { std::cout << "A animal sound" << '\n'; }

Animal::~Animal() {
    std::cout << "Default destructor for Animal is called" << '\n';
}
