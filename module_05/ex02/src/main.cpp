/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/07 21:27:33 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/10 19:17:42 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <unistd.h>

#include "../include/AForm.hpp"
#include "../include/Bureaucrat.hpp"
#include "../include/PresidentialPardonForm.hpp"
#include "../include/RobotomyRequestForm.hpp"
#include "../include/ShrubberyCreationForm.hpp"

class StderrCapture {
  private:
    std::string filename;
    FILE *original_stderr;

  public:
    StderrCapture(const std::string &fname) : filename(fname) {
        original_stderr = stderr;
        FILE *new_stderr = std::freopen(filename.c_str(), "w", stderr);
        if (!new_stderr) {
            throw std::runtime_error("Failed to redirect stderr");
        }
    }

    ~StderrCapture() {
        std::fflush(stderr);
        std::fclose(stderr);
        stderr = original_stderr;
    }

    bool checkContent() {
        std::fflush(stderr); // Ensure all data is written to the file
        std::ifstream file(filename);
        return file.peek() != std::ifstream::traits_type::eof();
    }

    void clearFile() {
        std::fflush(stderr); // Ensure all data is written to the file
        std::ofstream file(filename, std::ofstream::out | std::ofstream::trunc);
        file.close();
    }

    void restoreCerr() {
        std::fclose(stderr);
        std::freopen("/dev/tty", "a", stderr);
    }

    void rmFile() { std::remove(filename.c_str()); }
};

void testBureaucratEdgeCases() {
    std::cout << "\n--- Testing Bureaucrat Edge Cases ---\n";

    // Test creating bureaucrat with too high grade
    try {
        Bureaucrat tooHigh("TooHigh", -1);
        assert(false && "Should have thrown exception");
    } catch (const Bureaucrat::GradeTooHighException &) {
        static_assert(true, "");
    } catch (...) {
        assert(false && "Wrong exception type caught");
    }

    // Test creating bureaucrat with too high grade
    try {
        Bureaucrat tooHigh("TooHigh", 0);
        assert(false && "Should have thrown exception");
    } catch (const Bureaucrat::GradeTooHighException &) {
        static_assert(true, "");
    } catch (...) {
        assert(false && "Wrong exception type caught");
    }

    // Test creating bureaucrat with too low grade
    try {
        Bureaucrat tooLow("TooLow", 151);
        assert(false && "Should have thrown exception");
    } catch (const Bureaucrat::GradeTooLowException &) {
        static_assert(true, "");
    } catch (...) {
        assert(false && "Wrong exception type caught");
    }

    // Test incrementing highest grade
    {
        Bureaucrat b("EdgeCase", 1);
        try {
            b.incrementGrade();
            assert(false && "Should have thrown exception");
        } catch (const Bureaucrat::GradeTooHighException &) {
            static_assert(true, "");
        } catch (...) {
            assert(false && "Wrong exception type caught");
        }
    }

    // Test decrementing lowest grade
    {
        Bureaucrat b("EdgeCase", 150);
        try {
            b.decrementGrade();
            assert(false && "Should have thrown exception");
        } catch (const Bureaucrat::GradeTooLowException &) {
            static_assert(true, "");
        } catch (...) {
            assert(false && "Wrong exception type caught");
        }
    }
}

void testShrubberyCreationForm() {
    std::cout << "\n--- Testing ShrubberyCreationForm ---\n";

    ShrubberyCreationForm scf("home");
    Bureaucrat highGrade("HighGrade", 1);
    Bureaucrat lowGrade("LowGrade", 150);
    StderrCapture capture("error_output.txt");

    // Test signing with low grade
    try {
        lowGrade.signForm(scf);
        assert(!scf.getIsSigned() &&
               "Low grade bureaucrat shouldn't be able to sign");
    } catch (const AForm::GradeTooLowException &) {
        static_assert(true, "");
    } catch (...) {
        assert(false && "Wrong exception type caught");
    }

    // Test signing with high grade
    highGrade.signForm(scf);
    assert(scf.getIsSigned() && "Form should be signed");

    // Test execution with low grade
    try {
        lowGrade.executeForm(scf);
        assert(capture.checkContent() &&
               "Low grade bureaucrat shouldn't be able to execute");
        capture.clearFile();
    } catch (const AForm::GradeTooLowException &) {
        static_assert(true, "");
    } catch (...) {
        assert(false && "Wrong exception type caught");
    }

    // Test execution with high grade
    highGrade.executeForm(scf);

    // Check if file was created
    std::ifstream file("home_shrubbery");
    assert(file.good() && "File 'home_shrubbery' should have been created");
    file.close();

    // Test file creation with no write permissions
    ShrubberyCreationForm scfNoWrite("/root/no_permission");
    highGrade.signForm(scfNoWrite);
    try {
        highGrade.executeForm(scfNoWrite);
        assert(capture.checkContent() &&
               "Should have thrown exception for no write permission");
        capture.clearFile();
    } catch (const std::runtime_error &) {
        static_assert(true, "");
    } catch (...) {
        assert(false && "Wrong exception type caught");
    }
    capture.restoreCerr();
    capture.rmFile();
}

void testRobotomyRequestForm() {
    std::cout << "\n--- Testing RobotomyRequestForm ---\n";

    RobotomyRequestForm rrf("Bender");
    Bureaucrat highGrade("HighGrade", 1);
    Bureaucrat lowGrade("LowGrade", 150);
    StderrCapture capture("error_output.txt");

    // Test signing with low grade
    try {
        lowGrade.signForm(rrf);
        assert(capture.checkContent() &&
               "Low grade bureaucrat shouldn't be able to sign");
        capture.clearFile();
    } catch (const AForm::GradeTooLowException &) {
        static_assert(true, "");
    } catch (...) {
        assert(false && "Wrong exception type caught");
    }

    // Test signing with high grade
    highGrade.signForm(rrf);
    assert(rrf.getIsSigned() && "Form should be signed");

    // Test execution with low grade
    try {
        lowGrade.executeForm(rrf);
        assert(capture.checkContent() &&
               "Low grade bureaucrat shouldn't be able to execute");
        capture.clearFile();
    } catch (const AForm::GradeTooLowException &) {
        static_assert(true, "");
    } catch (...) {
        assert(false && "Wrong exception type caught");
    }

    // Test multiple executions to check 50% success rate
    srand(time(nullptr));
    int successes = 0;
    int failed = 0;
    int attempts = 1000;

    for (int i = 0; i < attempts; ++i) {
        try {
            highGrade.executeForm(rrf);
            if (capture.checkContent() == true) {
                failed++;
                capture.clearFile();
            } else {
                successes++;
            }
        } catch (...) {
        }
    }
    std::cout << "Succes: " << successes << " failed: " << failed << '\n';
    capture.restoreCerr();
    capture.rmFile();
}

void testPresidentialPardonForm() {
    std::cout << "\n--- Testing PresidentialPardonForm ---\n";

    PresidentialPardonForm ppf("Arthur Dent");
    Bureaucrat highGrade("HighGrade", 1);
    Bureaucrat lowGrade("LowGrade", 150);
    Bureaucrat mediumGrade("MediumGrade", 20);
    StderrCapture capture("error_output.txt");

    // Test signing with low grade
    try {
        lowGrade.signForm(ppf);
        assert(capture.checkContent() &&
               "Low grade bureaucrat shouldn't be able to sign");
        capture.restoreCerr();
    } catch (const AForm::GradeTooLowException &) {
        static_assert(true, "");
    } catch (...) {
        assert(false && "Wrong exception type caught");
    }

    // Test signing with medium grade
    mediumGrade.signForm(ppf);
    assert(ppf.getIsSigned());

    // Test execution with medium grade
    try {
        mediumGrade.executeForm(ppf);
        assert(capture.checkContent() &&
               "Medium grade bureaucrat shouldn't be able to execute");
        capture.clearFile();
    } catch (const AForm::GradeTooLowException &) {
        static_assert(true, "");
    } catch (...) {
        assert(false && "Wrong exception type caught");
    }

    // Test execution with high grade
    highGrade.executeForm(ppf);
    // Note: You might want to add a way to verify the pardon was issued
    capture.restoreCerr();
    capture.rmFile();
}

int main() {
    try {
        testBureaucratEdgeCases();
        testShrubberyCreationForm();
        testRobotomyRequestForm();
        testPresidentialPardonForm();
        std::cout << "All tests passed successfully!\n";
    } catch (const std::exception &e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Test failed with unknown exception\n";
        return 1;
    }

    return 0;
}
