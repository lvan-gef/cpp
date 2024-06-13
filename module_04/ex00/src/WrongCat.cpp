/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   WrongCat.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:33:04 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:33:04 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/WrongCat.hpp"

WrongCat::WrongCat() : WrongAnimal("WrongCat") {
    std::cout << "Default constructor for WrongCat is called" << '\n';
}

WrongCat::WrongCat(const WrongCat &rhs) : WrongAnimal(rhs) {
    std::cout << "Default copy constructor for WrongCat is called" << '\n';
}

WrongCat &WrongCat::operator=(const WrongCat &rhs) {
    std::cout << "Copy assignment constructor for WrongCat is called" << '\n';

    if (this != &rhs) {
        WrongAnimal::operator=(rhs);
    }

    return *this;
}

WrongCat::WrongCat(WrongCat &&rhs) noexcept : WrongAnimal(std::move(rhs)) {
    std::cout << "Default move constructor for WrongCat is called" << '\n';
}

WrongCat &WrongCat::operator=(WrongCat &&rhs) noexcept {
    std::cout << "Move assignment operator for WrongCat is called" << '\n';

    if (this != &rhs) {
        WrongAnimal::operator=(std::move(rhs));
    }

    return *this;
}

void WrongCat::makeSound() const { std::cout << "iea iea" << '\n'; }

WrongCat::~WrongCat() {
    std::cout << "Default destructor for WrongCat is called" << '\n';
}
