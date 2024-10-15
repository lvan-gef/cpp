/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Tester.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 20:29:33 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/15 16:53:29 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Tester.hpp"

static std::string captureOutput(const std::string &input) {
    // Redirect stdout and stderr
    std::streambuf *oldCout = std::cout.rdbuf();
    std::streambuf *oldCerr = std::cerr.rdbuf();
    std::stringstream captureCout;
    std::stringstream captureCerr;
    std::cout.rdbuf(captureCout.rdbuf());
    std::cerr.rdbuf(captureCerr.rdbuf());

    // Call the convert function
    ScalarConverter::convert(input);

    // Restore stdout and stderr
    std::cout.rdbuf(oldCout);
    std::cerr.rdbuf(oldCerr);

    // Combine captured output
    return captureCout.str() + captureCerr.str();
}

static void runTest(const std::string &input, const std::string &expected) {
    std::cout << "Testing input: " << input << std::endl;
    std::string result = captureOutput(input);
    std::cout << "Result:\n" << result << std::endl;
    std::cout << "Expected:\n" << expected << std::endl;

    assert(result == expected &&
           "Conversion result does not match expected output");
    std::cout << "Test passed!" << std::endl << std::endl;
}

void tester() {
    std::vector<std::pair<std::string, std::string>> testCases = {
        {"'a'", "char: 'a'\nint: 97\nfloat: 97.0f\ndouble: 97.0\n"},
        {"0", "char: Non displayable\nint: 0\nfloat: 0.0f\ndouble: 0.0\n"},
        {"42", "char: '*'\nint: 42\nfloat: 42.0f\ndouble: 42.0\n"},
        {"-42",
         "char: Non displayable\nint: -42\nfloat: -42.0f\ndouble: -42.0\n"},
        {"4.2f", "char: Non displayable\nint: 4\nfloat: 4.2f\ndouble: 4.2\n"},
        {"4.2", "char: Non displayable\nint: 4\nfloat: 4.2f\ndouble: 4.2\n"},
        {"nan",
         "char: Non displayable\nint: impossible\nfloat: nanf\ndouble: nan\n"},
        {"nanf",
         "char: Non displayable\nint: impossible\nfloat: nanf\ndouble: nan\n"},
        {"+inf",
         "char: Non displayable\nint: impossible\nfloat: inff\ndouble: +inf\n"},
        {"-inff", "char: Non displayable\nint: impossible\nfloat: "
                  "-inff\ndouble: -inf\n"},
        {"42.42.42", "Invalid input\n"} // Invalid input case
    };

    for (const auto &testCase : testCases) {
        try {
            runTest(testCase.first, testCase.second);
        } catch (const std::exception &e) {
            std::cerr << "Test failed for input \"" << testCase.first
                      << "\": " << e.what() << std::endl;
        }
    }

    std::cout << "All tests completed." << std::endl;
}
