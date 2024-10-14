#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include <chrono>
#include <iostream>

#include "./AForm.hpp"

class RobotomyRequestForm : public AForm {
  public:
    explicit RobotomyRequestForm(const std::string &name);

    RobotomyRequestForm(const RobotomyRequestForm &rhs);
    RobotomyRequestForm &operator=(const RobotomyRequestForm &rhs) = delete;

    RobotomyRequestForm(RobotomyRequestForm &&rhs) noexcept;
    RobotomyRequestForm &operator=(RobotomyRequestForm &&rhs) noexcept = delete;

    ~RobotomyRequestForm() override;

  protected:
    void executeAction() const override;

  private:
    std::string _target;
};

#endif // !ROBOTOMYREQUESTFORM_HPP
