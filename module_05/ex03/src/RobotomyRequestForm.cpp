/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   RobotomyRequestForm.cpp                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/07 21:27:33 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/07 21:27:33 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(const std::string &name)
    : AForm(name, 45, 72), _target(name) {
    std::cout << "Default constructor for RobotomyRequestForm is called"
              << '\n';
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &rhs)
    : AForm(rhs), _target(rhs._target) {
    std::cout << "Default copy constructor for RobotomyRequestForm is called"
              << '\n';
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm &&rhs) noexcept
    : AForm(std::move(rhs)), _target(std::move(rhs._target)) {
    std::cout << "Default move constructor for RobotomyRequestForm is called"
              << '\n';
}

void RobotomyRequestForm::executeAction() const {
    std::cout << "Drill baby Drill" << '\n';

    uint64_t time = std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::system_clock::now().time_since_epoch())
                        .count();

    if (time % 2) {
        std::cout << "We robotomized the form" << '\n';
    } else {
        std::cerr << "Failed to robotomized the form" << '\n';
    }
}

RobotomyRequestForm::~RobotomyRequestForm() {
    std::cout << "Default destructor for RobotomyRequestForm is called" << '\n';
}
