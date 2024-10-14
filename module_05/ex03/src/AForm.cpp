/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   AForm.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/07 21:27:17 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/13 17:18:08 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/AForm.hpp"
#include "../include/Bureaucrat.hpp"

AForm::AForm() : _name("Kees"), _exegrade(10), _signGrade(12) {
    std::cout << "Default constructor for AForm is called" << '\n';
}

AForm::AForm(const std::string &name)
    : _name(name), _exegrade(10), _signGrade(12) {
    std::cout << "Default constructor with name for AForm is called" << '\n';
    if (_name == "") {
        throw std::invalid_argument("Name can't be empty");
    }
}

AForm::AForm(int grade, int signGrade)
    : _name("Kees"), _exegrade(grade), _signGrade(signGrade) {
    std::cout
        << "Default constructor with grade and signGrade for AForm is called"
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

AForm::AForm(const std::string &name, int grade)
    : _name(name), _exegrade(grade), _signGrade(12) {
    std::cout << "Default constructor with name and grade for AForm is called"
              << '\n';

    if (_name == "") {
        throw std::invalid_argument("Name can't be empty");
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

AForm::AForm(const std::string &name, int grade, int signGrade)
    : _name(name), _exegrade(grade), _signGrade(signGrade) {
    std::cout << "Default constructor with name, grade and signGrade for AForm "
                 "is called"
              << '\n';

    if (_name == "") {
        throw std::invalid_argument("Name can't be empty");
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

AForm::AForm(const AForm &rhs)
    : _name(rhs._name), _exegrade(rhs._exegrade), _signGrade(rhs._signGrade) {
    std::cout << "Default copy constructor for AForm is called" << '\n';
}

AForm::AForm(AForm &&rhs) noexcept
    : _name(rhs._name), _exegrade(rhs._exegrade), _signGrade(rhs._signGrade) {
    std::cout << "Default move constructor for AForm is called" << '\n';
}

void AForm::beSigned(Bureaucrat &rhs) {
    std::cout << "bur\t" << rhs.getGrade() << "\tgrade\t" << _signGrade
              << std::endl;
    if (rhs.getGrade() > _signGrade) {
        throw GradeTooLowException();
    }

    _isSigned = true;
}

void AForm::execute(Bureaucrat const &executor) const {
    if (getIsSigned() != true) {
        throw std::runtime_error("Form is not signed");
    }

    if (executor.getGrade() > _signGrade) {
        throw GradeTooLowException();
    }

    executeAction();
}

std::string AForm::getName() const { return _name; }
int AForm::getGrade() const { return _exegrade; }
int AForm::getSignGrade() const { return _signGrade; }
bool AForm::getIsSigned() const { return _isSigned; }

AForm::~AForm() {
    std::cout << "Default destructor for AForm is called" << '\n';
}

const char *AForm::GradeTooHighException::what() const noexcept {
    return ("Grade is to high...\n");
}
const char *AForm::GradeTooLowException::what() const noexcept {
    return ("Grade is to low...\n");
}

std::ostream &operator<<(std::ostream &os, const AForm &rhs) {
    os << "AForm: " << rhs.getName() << " grade: " << rhs.getGrade()
       << " sign grade: " << rhs.getSignGrade()
       << " is Signed: " << (rhs.getIsSigned() ? "Yes" : "No") << '\n';
    return os;
}
