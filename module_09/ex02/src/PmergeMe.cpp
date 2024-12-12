#include "../include/PmergeMe.hpp"

PmergeMe::PmergeMe() {
    std::cout << "Default constructor for PmergeMe is called" << '\n';
}

PmergeMe::PmergeMe(const PmergeMe &rhs) {
    (void) rhs;
    std::cout << "Default copy constructor for PmergeMe is called" << '\n';
}

PmergeMe &PmergeMe::operator=(const PmergeMe &rhs) {
    std::cout << "Copy assigment constructor for PmergeMe is called" << '\n';
    if (this != &rhs) {

    }

    return *this;
}

PmergeMe::PmergeMe(PmergeMe && rhs) noexcept {
    (void) rhs;
    std::cout << "Default move constructor for PmergeMe is called" << '\n';
}

PmergeMe &PmergeMe::operator=(PmergeMe && rhs) noexcept {
    std::cout << "Move assigment constructor for PmergeMe is called" << '\n';
    if (this != &rhs) {

    }

    return *this;
}

PmergeMe::~PmergeMe() {
    std::cout << "Default destructor for PmergeMe is called" << '\n';
}
