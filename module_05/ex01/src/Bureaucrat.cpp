/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Bureaucrat.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/10 16:54:15 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/13 18:11:50 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Bureaucrat.hpp"
#include "../include/Form.hpp"

Bureaucrat::Bureaucrat() : name_("default"), grade_(max_grade_) {
    std::cout << "Default constructor for Bureaucrat is called" << '\n';
}

Bureaucrat::Bureaucrat(std::string name)
    : name_(std::move(name)), grade_(max_grade_) {
    std::cout << "Default constructor with name for Bureaucrat is called"
              << '\n';
}

Bureaucrat::Bureaucrat(int grade) : name_("default"), grade_(grade) {
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
    : name_(std::move(name)), grade_(grade) {
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
    : name_(rhs.name_), grade_(rhs.grade_) {
    std::cout << "Default copy constructor for Bureaucrat is called" << '\n';
}

Bureaucrat::Bureaucrat(Bureaucrat &&rhs) noexcept
    : name_(rhs.name_), grade_(rhs.grade_) {
    std::cout << "Default move constructor for Bureaucrat is called" << '\n';
}

std::string Bureaucrat::getName() const { return name_; }
int Bureaucrat::getGrade() const { return grade_; }

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

void Bureaucrat::signForm(Form &rhs) {
    try {
        rhs.beSigned(*this);
    } catch (Form::GradeTooLowException &e) {
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
    std::cout << "Default destructor for Bureaucrat(" << name_ << ") is called"
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
