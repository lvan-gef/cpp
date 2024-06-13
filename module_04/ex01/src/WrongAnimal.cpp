/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   WrongAnimal.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:33:41 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:33:41 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/WrongAnimal.hpp"

WrongAnimal::WrongAnimal() : type_("WrongAnimal") {
    std::cout << "Default constructor for WrongAnimal is called" << '\n';
}

WrongAnimal::WrongAnimal(std::string name) : type_(std::move(name)) {
    std::cout << "Named constructor for WrongAnimal is called" << '\n';
}

WrongAnimal::WrongAnimal(const WrongAnimal &rhs) : type_(rhs.type_) {
    std::cout << "Default copy constructor for WrongAnimal is called" << '\n';
}

WrongAnimal &WrongAnimal::operator=(const WrongAnimal &rhs) {
    std::cout << "Copy assignment constructor for WrongAnimal is called"
              << '\n';

    if (this != &rhs) {
        type_ = rhs.type_;
    }

    return *this;
}

WrongAnimal::WrongAnimal(WrongAnimal &&rhs) noexcept
    : type_(std::move(rhs.type_)) {
    std::cout << "Default move constructor for WrongAnimal is called" << '\n';
    rhs.type_.clear();
}

WrongAnimal &WrongAnimal::operator=(WrongAnimal &&rhs) noexcept {
    std::cout << "Move assignment operator for WrongAnimal is called" << '\n';

    if (this != &rhs) {
        type_ = std::move(rhs.type_);
        rhs.type_.clear();
    }

    return *this;
}

std::string WrongAnimal::getType() const { return this->type_; }

void WrongAnimal::makeSound() const { std::cout << "nanana nanana" << '\n'; }

WrongAnimal::~WrongAnimal() {
    std::cout << "Default destructor for WrongAnimal is called" << '\n';
}
