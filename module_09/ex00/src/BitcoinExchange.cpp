#include "../include/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
    std::cout << "Default constructor for BitcoinExchange is called" << '\n';
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &rhs) {
    (void)rhs;
    std::cout << "Default copy constructor for BitcoinExchange is called" << '\n';
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs) {
    std::cout << "Copy assigment constructor for BitcoinExchange is called" << '\n';
    if (this != &rhs) {

    }

    return *this;
}

BitcoinExchange::BitcoinExchange(BitcoinExchange && rhs) noexcept {
    (void)rhs;
    std::cout << "Default move constructor for BitcoinExchange is called" << '\n';
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange && rhs) noexcept {
    std::cout << "Move assigment constructor for BitcoinExchange is called" << '\n';
    if (this != &rhs) {

    }

    return *this;
}

BitcoinExchange::~BitcoinExchange() {
    std::cout << "Default destructor for BitcoinExchange is called" << '\n';
}
