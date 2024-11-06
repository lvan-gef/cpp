#include "../include/RPN.hpp"

RPN::RPN(int argc, char **argv) {

    std::cout << "Default constructor for RPN is called" << '\n';
}

RPN::RPN(const RPN &rhs) {
    (void)rhs;
    std::cout << "Default copy constructor for RPN is called" << '\n';
}

RPN &RPN::operator=(const RPN &rhs) {
    std::cout << "Copy assigment constructor for RPN is called" << '\n';
    if (this != &rhs) {
    }

    return *this;
}

RPN::RPN(RPN &&rhs) noexcept {
    (void)rhs;
    std::cout << "Default move constructor for RPN is called" << '\n';
}

RPN &RPN::operator=(RPN &&rhs) noexcept {
    std::cout << "Move assigment constructor for RPN is called" << '\n';
    if (this != &rhs) {
    }

    return *this;
}

RPN::~RPN() {
    std::cout << "Default destructor for RPN is called" << '\n';
}
