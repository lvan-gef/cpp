/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   AMateria.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:34:58 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:34:58 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/AMateria.hpp"
#include "../include/ICharacter.hpp"

AMateria::AMateria() : type_("Default") {
    std::cout << "Default constructor for AMateria is called" << '\n';
}

AMateria::AMateria(const std::string &type) : type_(type) {
    std::cout << "Named constructor for AMateria is called" << '\n';
}

AMateria::AMateria(const AMateria &rhs) : type_(rhs.type_) {
    std::cout << "Default copy constructor for AMateria is called" << '\n';
}

AMateria &AMateria::operator=(const AMateria &rhs) {
    std::cout << "Copy assignment operator for AMateria is called" << '\n';

    if (this != &rhs) {
        type_ = rhs.type_;
    }

    return *this;
}

AMateria::AMateria(AMateria &&rhs) noexcept : type_(std::move(rhs.type_)) {
    std::cout << "Default move constructor for AMateria is called" << '\n';
    rhs.type_.clear();
}

AMateria &AMateria::operator=(AMateria &&rhs) noexcept {
    std::cout << "Move assignment operator for AMateria is called" << '\n';

    if (this != &rhs) {
        type_ = rhs.type_;
        rhs.type_.clear();
    }
    return *this;
}

const std::string &AMateria::getType() const { return type_; }

void AMateria::use(ICharacter &target) {
    std::cout << "AMateria did something to " << target.getName() << '\n';
}

AMateria::~AMateria() {
    std::cout << "Default destructor for AMateria is called" << '\n';
}
