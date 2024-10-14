#include <iostream>
#include "Bureaucrat.hpp"
#include "Form.hpp"

void testBureaucratCreation() {
    std::cout << "Testing Bureaucrat Creation..." << std::endl;
    try {
        Bureaucrat b1("Alice", 151);  // Invalid grade, should throw GradeTooLowException
    } catch (const Bureaucrat::GradeTooLowException &e) {
        std::cout << "Caught GradeTooLowException as expected: " << e.what() << std::endl;
    }

    try {
        Bureaucrat b2("Bob", 0);  // Invalid grade, should throw GradeTooHighException
    } catch (const Bureaucrat::GradeTooHighException &e) {
        std::cout << "Caught GradeTooHighException as expected: " << e.what() << std::endl;
    }

    Bureaucrat b3("Charlie", 1);  // Valid grade
    std::cout << b3 << std::endl;

    Bureaucrat b4("Dave", 150);  // Valid grade
    std::cout << b4 << std::endl;

    std::cout << std::endl;
}

void testBureaucratCopyAndMove() {
    std::cout << "Testing Bureaucrat Copy and Move Constructors..." << std::endl;
    Bureaucrat b1("Alice", 50);
    Bureaucrat b2(b1);  // Copy constructor
    std::cout << "Copy constructed Bureaucrat: " << b2 << std::endl;

    Bureaucrat b3(std::move(b1));  // Move constructor
    std::cout << "Move constructed Bureaucrat: " << b3 << std::endl;

    std::cout << std::endl;
}

void testBureaucratIncrementDecrement() {
    std::cout << "Testing Bureaucrat Grade Increment and Decrement..." << std::endl;
    Bureaucrat b1("Alice", 2);

    b1.incrementGrade();
    std::cout << "After incrementing grade: " << b1 << std::endl;

    try {
        b1.incrementGrade();  // This should throw GradeTooHighException
    } catch (const Bureaucrat::GradeTooHighException &e) {
        std::cout << "Caught GradeTooHighException as expected: " << e.what() << std::endl;
    }

    b1.decrementGrade();
    std::cout << "After decrementing grade: " << b1 << std::endl;

    Bureaucrat b2("Bob", 149);
    b2.decrementGrade();
    std::cout << "After decrementing grade: " << b2 << std::endl;

    try {
        b2.decrementGrade();  // This should throw GradeTooLowException
    } catch (const Bureaucrat::GradeTooLowException &e) {
        std::cout << "Caught GradeTooLowException as expected: " << e.what() << std::endl;
    }

    std::cout << std::endl;
}

void testFormCreationAndSigning() {
    std::cout << "Testing Form Creation and Signing..." << std::endl;
    Bureaucrat b1("Alice", 50);
    Form f1("Form1", 75, 50);  // Valid form
    std::cout << f1 << std::endl;

    try {
        Form f2("Form2", 0, 50);  // Invalid exegrade, should throw GradeTooHighException
    } catch (const Form::GradeTooHighException &e) {
        std::cout << "Caught Form::GradeTooHighException as expected: " << e.what() << std::endl;
    }

    try {
        Form f3("Form3", 151, 50);  // Invalid exegrade, should throw GradeTooLowException
    } catch (const Form::GradeTooLowException &e) {
        std::cout << "Caught Form::GradeTooLowException as expected: " << e.what() << std::endl;
    }

    f1.beSigned(b1);
    std::cout << "After signing the form: " << f1 << std::endl;

    Bureaucrat b2("Bob", 100);
    try {
        f1.beSigned(b2);  // This should throw GradeTooLowException
    } catch (const Form::GradeTooLowException &e) {
        std::cout << "Caught Form::GradeTooLowException as expected: " << e.what() << std::endl;
    }

    std::cout << std::endl;
}

void testFormCopyAndMove() {
    std::cout << "Testing Form Copy and Move Constructors..." << std::endl;
    Form f1("Form1", 75, 50);

    Form f2(f1);  // Copy constructor
    std::cout << "Copy constructed Form: " << f2 << std::endl;

    Form f3(std::move(f1));  // Move constructor
    std::cout << "Move constructed Form: " << f3 << std::endl;

    std::cout << std::endl;
}

void testFormSigningWithBureaucrat() {
    std::cout << "Testing Form Signing with Bureaucrat..." << std::endl;
    Bureaucrat b1("Alice", 75);
    Bureaucrat b2("Bob", 50);
    Bureaucrat b3("Charlie", 150);

    Form f1("Form1", 100, 50);  // Execution grade: 100, Sign grade: 50
    Form f2("Form2", 150, 100); // Execution grade: 150, Sign grade: 100

    try {
        f1.beSigned(b1);  // This should succeed
        std::cout << b1.getName() << " successfully signed " << f1.getName() << std::endl;
    } catch (const std::exception &e) {
        std::cout << b1.getName() << " could not sign " << f1.getName() << ": " << e.what() << std::endl;
    }

    try {
        f2.beSigned(b3);  // This should fail
        std::cout << b3.getName() << " successfully signed " << f2.getName() << std::endl;
    } catch (const std::exception &e) {
        std::cout << b3.getName() << " could not sign " << f2.getName() << ": " << e.what() << std::endl;
    }

    std::cout << std::endl;
}

int main() {
    testBureaucratCreation();
    testBureaucratCopyAndMove();
    testBureaucratIncrementDecrement();
    testFormCreationAndSigning();
    testFormCopyAndMove();
    testFormSigningWithBureaucrat();

    return 0;
}
