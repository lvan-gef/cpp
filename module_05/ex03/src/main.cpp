/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/07 21:27:33 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/13 17:57:09 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <iostream>
#include "../include/Intern.hpp"
#include "../include/ShrubberyCreationForm.hpp"
#include "../include/RobotomyRequestForm.hpp"
#include "../include/PresidentialPardonForm.hpp"

void testInternCopyAndMove() {
    std::cout << '\n' << "Start Copy and Move test" << '\n';

    Intern intern1;
    AForm* form;

    // Test copy constructor
    Intern intern2(intern1);
    form = intern2.makeForm("shrubbery creation", "garden");
    assert(form != nullptr);
    delete form;

    // Test copy assignment
    Intern intern3;
    intern3 = intern1;
    form = intern3.makeForm("robotomy request", "Bender");
    assert(form != nullptr);
    delete form;

    // Test move constructor
    Intern intern4(std::move(intern1));
    form = intern4.makeForm("presidential pardon", "Zaphod");
    assert(form != nullptr);
    delete form;

    // Verify that intern4 (moved-to object) still works
    form = intern4.makeForm("shrubbery creation", "forest");
    assert(form != nullptr);
    delete form;

    // Test move assignment
    Intern intern5;
    intern5 = std::move(intern2);
    form = intern5.makeForm("robotomy request", "C-3PO");
    assert(form != nullptr);
    delete form;

    // Verify that intern5 (moved-to object) still works
    form = intern5.makeForm("presidential pardon", "R2-D2");
    assert(form != nullptr);
    delete form;
}


void testInternFormCreation() {
    Intern intern;
    AForm* form;

    // Test 1: Create ShrubberyCreationForm
    form = intern.makeForm("shrubbery creation", "garden");
    assert(form != nullptr);
    assert(dynamic_cast<ShrubberyCreationForm*>(form) != nullptr);
    assert(form->getName() == "garden");
    delete form;

    // Test 2: Create RobotomyRequestForm
    form = intern.makeForm("robotomy request", "Bender");
    assert(form != nullptr);
    assert(dynamic_cast<RobotomyRequestForm*>(form) != nullptr);
    assert(form->getName() == "Bender");
    delete form;

    // Test 3: Create PresidentialPardonForm
    form = intern.makeForm("presidential pardon", "Zaphod");
    assert(form != nullptr);
    assert(dynamic_cast<PresidentialPardonForm*>(form) != nullptr);
    assert(form->getName() == "Zaphod");
    delete form;

    // Test 4: Try to create non-existent form
    form = intern.makeForm("non-existent form", "target");
    assert(form == nullptr);

    // Test 5: Case sensitivity
    form = intern.makeForm("ROBOTOMY REQUEST", "Bender");
    assert(form == nullptr);

    // Test 6: Empty form name
    form = intern.makeForm("", "target");
    assert(form == nullptr);

    // Test 7: Empty target
    form = intern.makeForm("shrubbery creation", "");
    assert(form == nullptr);

    // Test 8: Whitespace in form name
    form = intern.makeForm("  shrubbery creation  ", "garden");
    assert(form == nullptr);
}

int main() {
    testInternFormCreation();
    std::cout << "Intern tests passed." << '\n';
    testInternCopyAndMove();
    std::cout << "Copy and move tests passed." << '\n';

    std::cout << "All tests passed successfully!" << '\n';
    return 0;
}
