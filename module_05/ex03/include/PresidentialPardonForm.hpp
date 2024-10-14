#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include <iostream>

#include "../include/AForm.hpp"

class PresidentialPardonForm : public AForm {
  public:
    explicit PresidentialPardonForm(const std::string &name);

    PresidentialPardonForm(const PresidentialPardonForm &rhs);
    PresidentialPardonForm &
    operator=(const PresidentialPardonForm &rhs) = delete;

    PresidentialPardonForm(PresidentialPardonForm &&rhs) noexcept;
    PresidentialPardonForm &
    operator=(PresidentialPardonForm &&rhs) noexcept = delete;

    ~PresidentialPardonForm() override;

  protected:
    void executeAction() const override;

  private:
    std::string _target;
};

#endif // !PRESIDENTIALPARDONFORM_HPP
