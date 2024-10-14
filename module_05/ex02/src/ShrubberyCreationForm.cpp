/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ShrubberyCreationForm.cpp                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/07 21:27:33 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/07 21:27:33 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &name)
    : AForm(name, 137, 145), _target(name) {
    std::cout << "Default constructor for ShrubberyCreationForm is called"
              << '\n';
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &rhs)
    : AForm(rhs), _target(rhs._target) {
    std::cout << "Default copy constructor for ShrubberyCreationForm is called"
              << '\n';
}

ShrubberyCreationForm::ShrubberyCreationForm(
    ShrubberyCreationForm &&rhs) noexcept
    : AForm(std::move(rhs)), _target(std::move(rhs._target)) {
    std::cout << "Default move constructor for ShrubberyCreationForm is called"
              << '\n';
    if (rhs._outfile.is_open()) {
        _outfile = std::move(rhs._outfile);
        rhs._outfile.close();
    }
}

void ShrubberyCreationForm::executeAction() const {
    if (!_outfile.is_open()) {
        _outfile.open(_target + "_shrubbery");
        if (!_outfile) {
            throw std::runtime_error("Cannot create file");
        }
    }

    _outfile << "    *    \n";
    _outfile << "   ***   \n";
    _outfile << "  *****  \n";
    _outfile << " ******* \n";
    _outfile << "    |    \n";

    _outfile.flush();
}

ShrubberyCreationForm::~ShrubberyCreationForm() {
    std::cout << "Default destructor for ShrubberyCreationForm is called"
              << '\n';
    if (_outfile.is_open()) {
        _outfile.close();
    }
}
