#ifndef INTERN_HPP
#define INTERN_HPP

#include <iostream>

#include "./AForm.hpp"

class Intern {
  public:
    Intern();

    Intern(const Intern &rhs);
    Intern &operator=(const Intern &rhs);

    Intern(Intern &&rhs) noexcept;
    Intern &operator=(Intern &&rhs) noexcept;

    AForm *makeForm(const std::string &name, const std::string &target);

    ~Intern();

  private:
    struct FormType {
        std::string name;
        AForm *(*creator)(const std::string &);
    };

    static const int NUM_FORM = 3;
    FormType formTypes[NUM_FORM];

    static AForm *createShrubby(const std::string &target);
    static AForm *createRobot(const std::string &target);
    static AForm *createPresident(const std::string &target);
};

#endif // !INTERN_HPP
