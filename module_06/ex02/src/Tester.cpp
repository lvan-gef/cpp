/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Tester.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 19:54:24 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/22 00:39:42 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Tester.hpp"
#include "../include/A.hpp"
#include "../include/B.hpp"
#include "../include/C.hpp"

// Helper function to capture cout output
std::string captureOutput(const std::function<void()> &func) {
    std::stringstream buffer;
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());
    func();
    std::cout.rdbuf(old);
    return buffer.str();
}

// Helper function to capture cerr output
std::string captureStderr(const std::function<void()> &func) {
    std::stringstream buffer;
    std::streambuf *old = std::cerr.rdbuf(buffer.rdbuf());
    func();
    std::cerr.rdbuf(old);
    return buffer.str();
}

std::pair<std::string, std::string>
captureOutputAndError(const std::function<void()> &func) {
    std::stringstream outBuffer, errBuffer;
    std::streambuf *oldOut = std::cout.rdbuf(outBuffer.rdbuf());
    std::streambuf *oldErr = std::cerr.rdbuf(errBuffer.rdbuf());
    func();
    std::cout.rdbuf(oldOut);
    std::cerr.rdbuf(oldErr);
    return std::make_pair(outBuffer.str(), errBuffer.str());
}

// Test functions
void testGenerator(const std::function<Base *()> &generatorFunc) {
    std::cout << "Testing generator()..." << '\n';

    // Redirect cout to a stringstream
    std::stringstream buffer;
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

    const int NUM_ITERATIONS = 10000;
    int countA = 0, countB = 0, countC = 0;

    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        Base *obj = generatorFunc();
        assert(obj != nullptr); // Ensure generator never returns nullptr

        if (dynamic_cast<A *>(obj))
            countA++;
        else if (dynamic_cast<B *>(obj))
            countB++;
        else if (dynamic_cast<C *>(obj))
            countC++;
        else
            assert(false); // Should never reach here

        delete obj;
    }

    // Restore the original buffer
    std::cout.rdbuf(old);

    std::cout << "A: " << countA << ", B: " << countB << ", C: " << countC
              << '\n';
}

void testIdentifyPointer(std::function<void(Base *)> identifyFunc) {
    std::cout << "Testing identify(Base*)..." << '\n';

    std::stringstream buffer;
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

    A a;
    B b;
    C c;

    assert(captureOutput([&]() { identifyFunc(&a); }) == "A\n");
    assert(captureOutput([&]() { identifyFunc(&b); }) == "B\n");
    assert(captureOutput([&]() { identifyFunc(&c); }) == "C\n");

    // Edge case: nullptr
    assert(captureStderr([identifyFunc]() { identifyFunc(nullptr); }) ==
           "Unknown type\n");

    // Restore the original buffer
    std::cout.rdbuf(old);
}

void testIdentifyReference(std::function<void(Base &)> identifyFunc) {
    std::cout << "Testing identify(Base&)..." << '\n';

    A a;
    B b;
    C c;

    std::pair<std::string, std::string> resultA =
        captureOutputAndError([&]() { identifyFunc(a); });
    std::pair<std::string, std::string> resultB =
        captureOutputAndError([&]() { identifyFunc(b); });
    std::pair<std::string, std::string> resultC =
        captureOutputAndError([&]() { identifyFunc(c); });

    assert(resultA.first == "A\n" && resultA.second.empty());
    assert(resultB.first == "B\n" && resultB.second.empty());
    assert(resultC.first == "C\n" && resultC.second.empty());
}

void testEdgeCases(const std::function<void(Base *)> &identifyFunc,
                   const std::function<void(Base &)> &identifyFuncRef) {
    std::cout << "Testing edge cases..." << '\n';

    D d;
    assert(captureStderr([&]() { identifyFunc(&d); }) == "Unknown type\n");

    // For reference version, it should print nothing (all casts fail)
    assert(captureStderr([&]() { identifyFuncRef(d); }) == "std::bad_cast\n");
}
