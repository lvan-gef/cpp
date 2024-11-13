#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <algorithm>
#include <climits>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "./FileHandler.hpp"
#include "./Utils.hpp"

struct ExchangeDay {
    std::string date;
    float value;
};

class BitcoinExchange {
  public:
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
    std::map<std::string, float> _db;
    std::string _dbSeperator;
    std::string _targetSeperator;
    int _maxValue;

    std::string _lineBuffer;
    std::vector<std::string> _tokenBuffer;
    std::ostringstream _errorBuffer;

    std::string _getSeperator(FileHandler &fh);
    bool _startsWith(const std::string &str);
    ExchangeDay _getExchangeData(const std::string &line,
                                 const std::string &separator);
    void _validateDate(std::string &line);
    void _checkDB(const ExchangeDay &ed);
    void _loadDB();
    float _findClosest(const std::string &target_date);
};

#endif // !BITCOINEXCHANGE_HPP
