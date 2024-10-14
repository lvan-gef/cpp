/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   PresidentialPardonForm.cpp                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/07 21:27:33 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/07 21:27:33 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(const std::string &name)
    : AForm(name, 5, 25), _target(name) {
    std::cout << "Default constructor for PresidentialPardonForm is called"
              << '\n';
}

PresidentialPardonForm::PresidentialPardonForm(
    const PresidentialPardonForm &rhs)
    : AForm(rhs), _target(rhs._target) {
    std::cout << "Default copy constructor for PresidentialPardonForm is called"
              << '\n';
}

PresidentialPardonForm::PresidentialPardonForm(
    PresidentialPardonForm &&rhs) noexcept
    : AForm(std::move(rhs)), _target(std::move(rhs._target)) {
    std::cout << "Default move constructor for PresidentialPardonForm is called"
              << '\n';
}

void PresidentialPardonForm::executeAction() const {
    std::cout << "Zaphod Beeblebrox has pardoned " << _target << '\n';
}

PresidentialPardonForm::~PresidentialPardonForm() {
    std::cout << "Default destructor for PresidentialPardonForm is called"
              << '\n';
}
