/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Bureaucrat.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/10 16:54:15 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/13 17:25:43 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Bureaucrat.hpp"
#include "../include/AForm.hpp"

Bureaucrat::Bureaucrat() : _name("default"), grade_(max_grade_) {
    std::cout << "Default constructor for Bureaucrat is called" << '\n';
}

Bureaucrat::Bureaucrat(std::string name)
    : _name(std::move(name)), grade_(max_grade_) {
    std::cout << "Default constructor with name for Bureaucrat is called"
              << '\n';
}

Bureaucrat::Bureaucrat(int grade) : _name("default"), grade_(grade) {
    std::cout << "Default constructor with grade for Bureaucrat is called"
              << '\n';
    if (grade_ < 1) {
        throw GradeTooHighException();
    }
    if (grade > max_grade_) {
        throw GradeTooLowException();
    }
}

Bureaucrat::Bureaucrat(std::string name, int grade)
    : _name(std::move(name)), grade_(grade) {
    std::cout
        << "Default constructor with name and grade for Bureaucrat is called"
        << '\n';
    if (grade_ < 1) {
        throw GradeTooHighException();
    }
    if (grade > max_grade_) {
        throw GradeTooLowException();
    }
}

Bureaucrat::Bureaucrat(const Bureaucrat &rhs)
    : _name(rhs._name), grade_(rhs.grade_) {
    std::cout << "Default copy constructor for Bureaucrat is called" << '\n';
}

Bureaucrat::Bureaucrat(Bureaucrat &&rhs) noexcept
    : _name(rhs._name), grade_(rhs.grade_) {
    std::cout << "Default move constructor for Bureaucrat is called" << '\n';
}

std::string Bureaucrat::getName() const { return _name; }
int Bureaucrat::getGrade() const { return grade_; }

void Bureaucrat::executeForm(AForm const &form) {
    try {
        form.execute(*this);
        std::cout << _name << " executed " << form.getName() << '\n';
    } catch (std::exception &e) {
        std::cerr << _name << " couldn't execute " << form.getName()
                  << " because " << e.what() << std::endl;
    }
}

void Bureaucrat::incrementGrade() {
    if (grade_ > 1) {
        grade_--;
    } else {
        throw GradeTooHighException();
    }
}

void Bureaucrat::decrementGrade() {
    if (grade_ < max_grade_) {
        grade_++;
    } else {
        throw GradeTooLowException();
    }
}

void Bureaucrat::signForm(AForm &rhs) {
    try {
        rhs.beSigned(*this);
    } catch (AForm::GradeTooLowException &e) {
        std::cerr << "Bureaucrat couldn't sign the form because it has no "
                     "rigth to do that...: "
                  << e.what() << '\n';
        return;
    } catch (std::exception &e) {
        std::cerr << "A unknow error: " << e.what() << '\n';
        return;
    }
    std::cout << "Bureaucrat signed the form.";
}

Bureaucrat::~Bureaucrat() {
    std::cout << "Default destructor for Bureaucrat(" << _name << ") is called"
              << '\n';
}

const char *Bureaucrat::GradeTooHighException::what() const noexcept {
    return ("Grade is to high...\n");
}
const char *Bureaucrat::GradeTooLowException::what() const noexcept {
    return ("Grade is to low...\n");
}

std::ostream &operator<<(std::ostream &os, const Bureaucrat &rhs) {
    os << rhs.getName() << ", bureaucrat grade " << rhs.getGrade() << "\n";
    return os;
}
