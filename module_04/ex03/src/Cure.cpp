/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Cure.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:34:59 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:34:59 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cure.hpp"

Cure::Cure() : AMateria("cure") {
    std::cout << "Default constructor for Cure is called" << '\n';
}

Cure::Cure(const Cure &rhs) : AMateria(rhs.type_) {
    std::cout << "Default copy constructor for Cure is called" << '\n';
}

Cure &Cure::operator=(const Cure &rhs) {
    std::cout << "Copy assignment operator for Cure is called" << '\n';

    if (this != &rhs) {
        AMateria::operator=(rhs);
    }

    return *this;
}

Cure::Cure(Cure &&rhs) noexcept : AMateria(std::move(rhs)) {
    std::cout << "Default move constructor for Cure is called" << '\n';
    rhs.type_.clear();
}

Cure &Cure::operator=(Cure &&rhs) noexcept {
    std::cout << "Move assigment operator for Cure is called" << '\n';

    if (this != &rhs) {
        AMateria::operator=(std::move(rhs));
        rhs.type_.clear();
    }

    return *this;
}

AMateria *Cure::clone() const { return new (std::nothrow) Cure(*this); }

void Cure::use(ICharacter &target) {
    std::cout << "Cure: * heals " << target.getName() << "'s wounds *" << '\n';
}

Cure::~Cure() { std::cout << "Default destructor for Cure is called" << '\n'; }
