/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Ice.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:34:59 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:34:59 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Ice.hpp"

Ice::Ice() : AMateria("ice") {
    std::cout << "Default constructor for Ice is called" << '\n';
}

Ice::Ice(const Ice &rhs) : AMateria(rhs.type_) {
    std::cout << "Default copy constructor for Ice is called" << '\n';
}

Ice &Ice::operator=(const Ice &rhs) {
    std::cout << "Copy assignment operator for Ice is called" << '\n';

    if (this != &rhs) {
        AMateria::operator=(rhs);
    }

    return *this;
}

Ice::Ice(Ice &&rhs) noexcept : AMateria(std::move(rhs)) {
    std::cout << "Default move constructor for Ice is called" << '\n';
    rhs.type_.clear();
}

Ice &Ice::operator=(Ice &&rhs) noexcept {
    std::cout << "Move assignment operator for Ice is called" << '\n';

    if (this != &rhs) {
        AMateria::operator=(std::move(rhs));
        rhs.type_.clear();
    }

    return *this;
}

AMateria *Ice::clone() const { return new (std::nothrow) Ice(*this); }

void Ice::use(ICharacter &target) {
    std::cout << "Ice: * shoots an ice bolt at " << target.getName() << " *"
              << '\n';
}

Ice::~Ice() { std::cout << "Default destructor for Ice is called" << '\n'; }
