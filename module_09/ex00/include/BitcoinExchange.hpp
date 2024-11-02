#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>

class BitcoinExchange {
public:
    BitcoinExchange();

    BitcoinExchange(const BitcoinExchange &rhs);
    BitcoinExchange &operator=(const BitcoinExchange &rhs);

    BitcoinExchange(BitcoinExchange && rhs) noexcept;
    BitcoinExchange &operator=(BitcoinExchange && rhs) noexcept;

    ~BitcoinExchange();
};

#endif // !BITCOINEXCHANGE_HPP
