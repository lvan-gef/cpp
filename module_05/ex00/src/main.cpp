/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/13 21:30:54 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/13 13:40:25 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Bureaucrat.hpp"

int main() {
    Bureaucrat bc = Bureaucrat();
    std::cout << "\n";
    try {
        bc.decrementGrade();
    } catch (Bureaucrat::GradeTooLowException &e) {
        std::cout << bc;
        std::cerr << e.what();
    }
    std::cout << "-------------------------------" << "\n";

    for (int i = 151; i > 0; i--) {
        try {
            bc.incrementGrade();
        } catch (Bureaucrat::GradeTooHighException &e) {
            std::cout << bc;
            std::cerr << e.what();
            break;
        }
    }
    std::cout << "-------------------------------" << "\n";

    try {
        Bureaucrat bc1 = Bureaucrat(0);
    } catch (std::exception &e) {
        std::cerr << e.what();
    }

    std::cout << "-------------------------------" << "\n";
    try {
        Bureaucrat bc1 = Bureaucrat(-20);
    } catch (std::exception &e) {
        std::cerr << e.what();
    }
    std::cout << "-------------------------------" << "\n";

    try {
        Bureaucrat bc1 = Bureaucrat(1874259246);
    } catch (std::exception &e) {
        std::cerr << e.what();
    }
    std::cout << "-------------------------------" << "\n";

    try {
        Bureaucrat bc1 = Bureaucrat(151);
    } catch (std::exception &e) {
        std::cerr << e.what();
    }
    std::cout << "-------------------------------" << "\n";

    Bureaucrat bc1 = Bureaucrat("Luuk");
    try {
        bc1.decrementGrade();
    } catch (Bureaucrat::GradeTooLowException &e) {
        std::cout << bc1;
        std::cerr << e.what();
    }
    std::cout << "-------------------------------" << "\n";

    for (int i = 151; i > 0; i--) {
        try {
            bc1.incrementGrade();
        } catch (Bureaucrat::GradeTooHighException &e) {
            std::cout << bc1;
            std::cerr << e.what();
            break;
        }
    }
    std::cout << "-------------------------------" << "\n";

    Bureaucrat bc2 = Bureaucrat("Kees", 15);
    for (int i = bc2.getGrade(); i < 160; i++) {
        try {
            bc2.decrementGrade();
        } catch (Bureaucrat::GradeTooLowException &e) {
            std::cout << bc2;
            std::cerr << e.what();
            break;
        }
    }
    std::cout << "-------------------------------" << "\n";

    for (int i = 151; i > 0; i--) {
        try {
            bc2.incrementGrade();
        } catch (Bureaucrat::GradeTooHighException &e) {
            std::cout << bc2;
            std::cerr << e.what();
            break;
        }
    }
    std::cout << "-------------------------------" << "\n";

    std::cout << "\n";
}
