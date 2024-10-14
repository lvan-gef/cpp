#include "../include/Intern.hpp"
#include "../include/PresidentialPardonForm.hpp"
#include "../include/RobotomyRequestForm.hpp"
#include "../include/ShrubberyCreationForm.hpp"

Intern::Intern() {
    formTypes[0] = {"shrubbery creation", &createShrubby};
    formTypes[1] = {"robotomy request", &createRobot};
    formTypes[2] = {"presidential pardon", &createPresident};
    std::cout << "Default constructor for Intern is called" << '\n';
}

Intern::Intern(const Intern &rhs) : formTypes() {
    std::cout << "Default copy constructor for Intern is called" << '\n';
    std::copy(rhs.formTypes, rhs.formTypes + NUM_FORM, formTypes);
}

Intern &Intern::operator=(const Intern &rhs) {
    std::cout << "Copy assigment constructor for Intern is called" << '\n';

    if (this != &rhs) {
        std::copy(std::begin(rhs.formTypes), std::end(rhs.formTypes),
                  std::begin(formTypes));
    }

    return *this;
}

Intern::Intern(Intern &&rhs) noexcept : formTypes() {
    std::cout << "Default move constructor for Intern is called" << '\n';
    std::move(rhs.formTypes, rhs.formTypes + NUM_FORM, formTypes);
}

Intern &Intern::operator=(Intern &&rhs) noexcept {
    std::cout << "Move assigment constructor for Intern is called" << '\n';
    if (this != &rhs) {
        std::move(std::begin(rhs.formTypes), std::end(rhs.formTypes),
                  std::begin(formTypes));
    }

    return *this;
}

AForm *Intern::createShrubby(const std::string &target) {
    return new ShrubberyCreationForm(target);
}

AForm *Intern::createRobot(const std::string &target) {
    return new RobotomyRequestForm(target);
}

AForm *Intern::createPresident(const std::string &target) {
    return new PresidentialPardonForm(target);
}

AForm *Intern::makeForm(const std::string &name, const std::string &target) {
    for (int i = 0; i < NUM_FORM; ++i) {
        if (formTypes[i].name == name) {
            try {
                AForm *form = formTypes[i].creator(target);
                std::cout << "Intern creates " << name << std::endl;
                return form;
            } catch (const std::exception &e) {
                std::cerr << "Error creating form: " << e.what() << '\n';
                return nullptr;
            }
        }
    }
    std::cerr << "Error: Unknown form type '" << name << "'" << std::endl;
    return nullptr;
}

Intern::~Intern() {
    std::cout << "Default destructor for Intern is called" << '\n';
}
