#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <array>
#include <map>
#include <sstream>

#include "./FileHandler.hpp"

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

    ~BitcoinExchange();

  public:
    void getResult(const std::string &file);

  public:
    class BE : public std::runtime_error {
      public:
        explicit BE(const std::string &msg);
    };

  private:
    FileHandler _fd;
    std::map<std::string, float> _db;
    std::array<std::string, 2> _tokenBuffer;
    char _dbSeperator;
    char _targetSeperator;
    float _maxValue;
    std::string _lineBuffer;
    std::ostringstream _errorBuffer;

  private:
    char _getSeperator(FileHandler &fh);
    bool _startsWith(const std::string &str) noexcept;
    ExchangeDay _getExchangeData(const std::string &line, const char separator);
    void _validateDate(const std::string &line);
    void _checkDB(const ExchangeDay &ed);
    void _loadDB();
    float _findClosest(const std::string &target_date);
};

#endif // !BITCOINEXCHANGE_HPP
