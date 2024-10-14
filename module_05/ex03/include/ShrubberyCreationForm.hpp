#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include <fstream>
#include <iostream>
#include <string>

#include "../include/AForm.hpp"

class ShrubberyCreationForm : public AForm {
  public:
    explicit ShrubberyCreationForm(const std::string &name);

    ShrubberyCreationForm(const ShrubberyCreationForm &rhs);
    ShrubberyCreationForm &operator=(const ShrubberyCreationForm &rhs) = delete;

    ShrubberyCreationForm(ShrubberyCreationForm &&rhs) noexcept;
    ShrubberyCreationForm &
    operator=(ShrubberyCreationForm &&rhs) noexcept = delete;

    ~ShrubberyCreationForm() override;

  protected:
    void executeAction() const override;

  private:
    std::string _target;
    mutable std::ofstream _outfile;
};

#endif // !SHRUBBERYCREATIONFORM_HPP
