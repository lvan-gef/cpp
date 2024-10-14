/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Form.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/13 20:19:05 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/13 18:13:37 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>
#include <ostream>
#include <string>

#include "./Bureaucrat.hpp"

class Form {
  public:
    Form();
    explicit Form(std::string name);
    explicit Form(int grade, int signGrade);
    explicit Form(std::string name, int grade);
    explicit Form(std::string name, int grade, int signGrade);

    Form(const Form &rhs);
    Form &operator=(const Form &rhs) = delete;

    Form(Form &&rhs) noexcept;
    Form &operator=(Form &&rhs) noexcept = delete;

    void beSigned(const Bureaucrat &rhs);

    std::string getName() const;
    int getGrade() const;
    int getSignGrade() const;
    bool getIsSigned() const;

    class GradeTooHighException : public std::exception {
      public:
        const char *what() const noexcept override;
    };
    class GradeTooLowException : public std::exception {
      public:
        const char *what() const noexcept override;
    };

    ~Form();

  private:
    const std::string _name;
    const int _exegrade;
    const int _signGrade;
    bool _isSigned = false;
    static const int _min_grade = 1;
    static const int _max_grade = 150;
};

std::ostream &operator<<(std::ostream &os, const Form &rhs);

#endif // !FORM_HPP
