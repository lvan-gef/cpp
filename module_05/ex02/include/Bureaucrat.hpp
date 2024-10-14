/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Bureaucrat.hpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/10 16:56:27 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/10 17:54:12 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <ostream>
#include <string>

class AForm; // Forward declaration

class Bureaucrat {
  public:
    Bureaucrat();
    explicit Bureaucrat(std::string name);
    explicit Bureaucrat(int grade);
    explicit Bureaucrat(std::string name, int grade);

    Bureaucrat(const Bureaucrat &rhs);
    Bureaucrat &operator=(const Bureaucrat &rhs) = delete;

    Bureaucrat(Bureaucrat &&rhs) noexcept;
    Bureaucrat &operator=(Bureaucrat &&rhs) noexcept = delete;

    std::string getName() const;
    int getGrade() const;

    void executeForm(AForm const &form);

    void incrementGrade();
    void decrementGrade();
    void signForm(AForm &rhs);

    class GradeTooHighException : public std::exception {
      public:
        const char *what() const noexcept override;
    };

    class GradeTooLowException : public std::exception {
      public:
        const char *what() const noexcept override;
    };

    ~Bureaucrat();

  private:
    const std::string _name;
    int grade_;
    static const int max_grade_ = 150;
};

std::ostream &operator<<(std::ostream &os, const Bureaucrat &rhs);

#endif // !BUREAUCRAT_HPP
