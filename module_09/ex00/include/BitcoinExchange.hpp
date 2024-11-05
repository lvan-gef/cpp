#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <algorithm>
#include <climits>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "./FileHandler.hpp"
#include "./Utils.hpp"

struct ExchangeDay {
    std::string date;
    double value;
};

class BitcoinExchange {
  public:
    BitcoinExchange();
    explicit BitcoinExchange(const std::string &file);

    BitcoinExchange(const BitcoinExchange &rhs) = delete;
    BitcoinExchange &operator=(const BitcoinExchange &rhs) = delete;

    BitcoinExchange(BitcoinExchange &&rhs) noexcept;
    BitcoinExchange &operator=(BitcoinExchange &&rhs) noexcept;

    void getResult(const std::string &file);

    class BE : public std::runtime_error {
      public:
        explicit BE(const std::string &msg);
    };

    ~BitcoinExchange();

  private:
    FileHandler _fd;
    std::map<std::string, double> _db;
    std::string _dbSeperator;
    std::string _targetSeperator;

    void _setSeperator(FileHandler &ft, FileHandler &fd);
    bool _startsWith(const std::string &str);
    ExchangeDay _getExchangeData(std::string &line, std::string &seperator);
    void _validateDate(std::string &line);
    void _checkDB(ExchangeDay ed);
    std::pair<std::string, double> _findClosest(const std::string &target_date);
};

#endif // !BITCOINEXCHANGE_HPP
