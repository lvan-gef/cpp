/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   AAnimal.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:34:27 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:34:27 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/AAnimal.hpp"

AAnimal::AAnimal() : type_("Animal") {
    std::cout << "Default constructor for AAnimal is called" << '\n';
}

AAnimal::AAnimal(std::string name) : type_(std::move(name)) {
    std::cout << "Default constructor for AAnimal is called" << '\n';
}

AAnimal::AAnimal(const AAnimal &rhs) : type_(rhs.type_) {
    std::cout << "Default copy constructor for AAnimal is called" << '\n';
}

AAnimal &AAnimal::operator=(const AAnimal &rhs) {
    std::cout << "Copy assignment constructor for AAnimal is called" << '\n';

    if (this != &rhs) {
        type_ = rhs.type_;
    }

    return *this;
}

AAnimal::AAnimal(AAnimal &&rhs) noexcept : type_(std::move(rhs.type_)) {
    std::cout << "Default move constructor for AAnimal is called" << '\n';
    rhs.type_.clear();
}

AAnimal &AAnimal::operator=(AAnimal &&rhs) noexcept {
    std::cout << "Move assigment operator for AAnimal is called" << '\n';

    if (this != &rhs) {
        type_ = std::move(rhs.type_);
        rhs.type_.clear();
    }

    return *this;
}

AAnimal::~AAnimal() {
    std::cout << "Default destructor for AAnimal is called" << '\n';
}
