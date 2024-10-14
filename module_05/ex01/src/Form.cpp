/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Form.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/13 20:19:01 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/13 18:13:37 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Form.hpp"

Form::Form() : _name("Kees"), _exegrade(10), _signGrade(12) {
    std::cout << "Default constructor for Form is called" << '\n';
}

Form::Form(std::string name)
    : _name(std::move(name)), _exegrade(10), _signGrade(12) {
    std::cout << "Default constructor with name for Form is called" << '\n';
    if (_name == "") {
        throw "Name can't be empty...\n";
    }
}

Form::Form(int grade, int signGrade)
    : _name("Kees"), _exegrade(grade), _signGrade(signGrade) {
    std::cout
        << "Default constructor with grade and signGrade for Form is called"
        << '\n';
    if (_exegrade < _min_grade) {
        throw GradeTooHighException();
    }
    if (_exegrade > _max_grade) {
        throw GradeTooLowException();
    }

    if (_signGrade < _min_grade) {
        throw GradeTooHighException();
    }
    if (_signGrade > _max_grade) {
        throw GradeTooLowException();
    }
}

Form::Form(std::string name, int grade)
    : _name(std::move(name)), _exegrade(grade), _signGrade(12) {
    std::cout << "Default constructor with name and grade for Form is called"
              << '\n';

    if (_name == "") {
        throw "Name can't be empty...\n";
    }

    if (_exegrade < 1) {
        throw GradeTooHighException();
    }
    if (_exegrade > _min_grade) {
        throw GradeTooLowException();
    }

    if (_signGrade < _min_grade) {
        throw GradeTooHighException();
    }
    if (_signGrade > _max_grade) {
        throw GradeTooLowException();
    }
}

Form::Form(std::string name, int grade, int signGrade)
    : _name(std::move(name)), _exegrade(grade), _signGrade(signGrade) {
    std::cout << "Default constructor with name, grade and signGrade for Form "
                 "is called"
              << '\n';

    if (_name == "") {
        throw "Name can't be empty...\n";
    }

    if (_exegrade < _min_grade) {
        throw GradeTooHighException();
    }
    if (_exegrade > _max_grade) {
        throw GradeTooLowException();
    }

    if (_signGrade < _min_grade) {
        throw GradeTooHighException();
    }
    if (_signGrade > _max_grade) {
        throw GradeTooLowException();
    }
}

Form::Form(const Form &rhs)
    : _name(rhs._name), _exegrade(rhs._exegrade), _signGrade(rhs._signGrade) {
    std::cout << "Default copy constructor for Form is called" << '\n';
}

Form::Form(Form &&rhs) noexcept
    : _name(rhs._name), _exegrade(rhs._exegrade), _signGrade(rhs._signGrade) {
    std::cout << "Default move constructor for Form is called" << '\n';
}

void Form::beSigned(const Bureaucrat &rhs) {
    if (rhs.getGrade() > _signGrade) {
        throw GradeTooLowException();
    }

    _isSigned = true;
}

std::string Form::getName() const { return _name; }
int Form::getGrade() const { return _exegrade; }
int Form::getSignGrade() const { return _signGrade; }
bool Form::getIsSigned() const { return _isSigned; }

Form::~Form() { std::cout << "Default destructor for Form is called" << '\n'; }

const char *Form::GradeTooHighException::what() const noexcept {
    return ("Grade is to high...\n");
}
const char *Form::GradeTooLowException::what() const noexcept {
    return ("Grade is to low...\n");
}

std::ostream &operator<<(std::ostream &os, const Form &rhs) {
    os << "Form: " << rhs.getName() << " grade: " << rhs.getGrade()
       << " sign grade: " << rhs.getSignGrade()
       << " is Signed: " << (rhs.getIsSigned() ? "Yes" : "No") << '\n';
    return os;
}
