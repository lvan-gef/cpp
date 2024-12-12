#include "../include/PmergeMeArray.hpp"

PmergeMeArray::PmergeMeArray() {
    std::cout << "Default constructor for PmergeMeArray is called" << '\n';
}

PmergeMeArray::PmergeMeArray(const PmergeMeArray &rhs) {
    (void) rhs;
    std::cout << "Default copy constructor for PmergeMeArray is called" << '\n';
}

PmergeMeArray &PmergeMeArray::operator=(const PmergeMeArray &rhs) {
    std::cout << "Copy assigment constructor for PmergeMeArray is called" << '\n';
    if (this != &rhs) {

    }

    return *this;
}

PmergeMeArray::PmergeMeArray(PmergeMeArray && rhs) noexcept {
    (void) rhs;
    std::cout << "Default move constructor for PmergeMeArray is called" << '\n';
}

PmergeMeArray &PmergeMeArray::operator=(PmergeMeArray && rhs) noexcept {
    std::cout << "Move assigment constructor for PmergeMeArray is called" << '\n';
    if (this != &rhs) {

    }

    return *this;
}

PmergeMeArray::~PmergeMeArray() {
    std::cout << "Default destructor for PmergeMeArray is called" << '\n';
}
