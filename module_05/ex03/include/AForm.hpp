#ifndef AFORM_HPP
#define AFORM_HPP

#include <iostream>
#include <string>

class Bureaucrat; // Forward declaration

class AForm {
  public:
    AForm &operator=(const AForm &rhs) = delete;
    AForm &operator=(AForm &&rhs) noexcept = delete;

    virtual void beSigned(Bureaucrat &rhs);
    void execute(Bureaucrat const &executor) const;

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

    virtual ~AForm() = 0;

  protected:
    AForm();

    explicit AForm(const std::string &name);
    explicit AForm(int grade, int signGrade);
    explicit AForm(const std::string &name, int grade);
    explicit AForm(const std::string &name, int grade, int signGrade);

    AForm(const AForm &rhs);
    AForm(AForm &&rhs) noexcept;

    virtual void executeAction() const = 0;

  private:
    const std::string _name;
    const int _exegrade;
    const int _signGrade;
    bool _isSigned = false;
    static const int _min_grade = 1;
    static const int _max_grade = 150;
};

std::ostream &operator<<(std::ostream &os, const AForm &rhs);

#endif // !AFORM_HPP
