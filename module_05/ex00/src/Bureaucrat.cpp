/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Bureaucrat.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/10 16:54:15 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/08/13 21:26:14 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Bureaucrat.hpp"

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
