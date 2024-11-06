#include "../include/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : _fd(), _maxValue(1000) {
}

BitcoinExchange::BitcoinExchange(const std::string &file) : _fd(file), _maxValue(1000) {
}

BitcoinExchange::BitcoinExchange(BitcoinExchange &&rhs) noexcept
    : _fd(std::move(rhs._fd)), _maxValue(rhs._maxValue) {
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange &&rhs) noexcept {
    if (this != &rhs) {
        _fd = std::move(rhs._fd);
        _maxValue = rhs._maxValue;
    }

    return *this;
}

void BitcoinExchange::getResult(const std::string &file) {
    FileHandler ft;

    try {
        ft = FileHandler(file);
    } catch (FileHandler::FileError &e) {
        throw BitcoinExchange::BE(e.what());
    } catch (...) {
        throw BitcoinExchange::BE("getResult: FileHandler: Unknown error");
    }

    try {
        _setSeperator(_fd, ft);
    } catch (BitcoinExchange::BE &) {
        throw;
    }

    ExchangeDay targetED;
    while (ft.isEof() != true) {
        try {
            std::string targetValue = ft.gnl();
            targetED = _getExchangeData(targetValue, _targetSeperator);
            _checkDB(targetED);
        } catch (FileHandler::FileError &) {
            throw;
        } catch (BitcoinExchange::BE &e) {
            std::cerr << "Error: " << e.what() << '\n';
        } catch (FileHandler::FileEOF &) {
            break;
        }
    }
}

BitcoinExchange::~BitcoinExchange() {
}

// private methods
bool BitcoinExchange::_startsWith(const std::string &str) {
    uint8_t startSize = 4;

    if (str.length() <= startSize) {
        return false;
    }

    if (str.compare(0, startSize, "date") != 0) {
        return false;
    }

    return true;
}

void BitcoinExchange::_setSeperator(FileHandler &fd, FileHandler &ft) {
    std::string targetHeader;
    std::string dbHeader;
    const int headerSize = 5;

    try {
        targetHeader = ft.gnl();
        dbHeader = fd.gnl();
    } catch (FileHandler::FileEOF &e) {
        throw BitcoinExchange::BE(e.what());
    } catch (FileHandler::FileError &e) {
        throw BitcoinExchange::BE(e.what());
    }

    const uint8_t startSize = 4;
    char nextChar = dbHeader[startSize];

    if (_startsWith(dbHeader) != true) {
        throw BitcoinExchange::BE("First line of '" + fd.getFilename() +
                                  "' must start with: 'date'");
    }

    if (_startsWith(targetHeader) != true) {
        throw BitcoinExchange::BE("First line of '" + ft.getFilename() +
                                  "' must start with: 'date'");
    }

    if (nextChar == ' ' && dbHeader.length() >= headerSize) {
        nextChar = dbHeader[startSize + 1];
    }

    std::vector<std::string> validSeparators = {",", ";", "\t", "|", " "};
    auto it = std::find_if(validSeparators.begin(), validSeparators.end(),
                           [nextChar](const std::string &sep) {
                               return !sep.empty() && sep[0] == nextChar;
                           });
    if (it == validSeparators.end()) {
        throw BitcoinExchange::BE("Could not found a valid separator for DB");
    }
    _dbSeperator = *it;

    nextChar = targetHeader[startSize];
    if (nextChar == ' ' && targetHeader.length() >= headerSize) {
        nextChar = targetHeader[startSize + 1];
    }
    it = std::find_if(validSeparators.begin(), validSeparators.end(),
                      [nextChar](const std::string &sep) {
                          return !sep.empty() && sep[0] == nextChar;
                      });
    if (it == validSeparators.end()) {
        throw BitcoinExchange::BE(
            "Could not found a valid separator for target");
    }
    _targetSeperator = *it;
}

ExchangeDay BitcoinExchange::_getExchangeData(std::string &line,
                                              std::string &seperator) {
    std::vector<std::string> tokens;
    std::istringstream lineStream(line);
    std::string token;

    while (std::getline(lineStream, token, seperator[0])) {
        token.erase(0, token.find_first_not_of(" \t"));
        token.erase(token.find_last_not_of(" \t") + 1);
        tokens.push_back(token);
    }

    if (tokens.size() != 2) {
        throw BitcoinExchange::BE(
            "Invalid format for input: '" + line + "', expected 2 '" +
            seperator +
            "' separated values, got: " + std::to_string(tokens.size()));
    }

    ExchangeDay ed;
    try {
        trim(tokens[0]);
        _validateDate(tokens[0]);
        ed.date = tokens[0];
    } catch (BitcoinExchange::BE &) {
        throw;
    }

    try {
        ed.value = std::stod(tokens[1]);
        if (ed.value > INT_MAX or ed.value < _maxValue) {
            throw BitcoinExchange::BE("value must be 0.0 and less then " +
                                      std::to_string(_maxValue) + "  got: '" +
                                      std::to_string(ed.value) + "'");
        } else if (ed.value < 0) {
            throw BitcoinExchange::BE("value must be 0.0 or more got: '" +
                                      std::to_string(ed.value) + "'");
        }
    } catch (std::invalid_argument &e) {
        throw BitcoinExchange::BE("value: '" + tokens[1] +
                                  "' is not a valid float... (" + e.what() +
                                  ")");
    } catch (std::out_of_range &) {
        throw BitcoinExchange::BE("Invalid float (out of range) for value");
    }

    return ed;
}

void BitcoinExchange::_validateDate(std::string &line) {
    std::regex date_pattern(
        "^\\d{4}-(?:0[1-9]|1[0-2])-(?:0[1-9]|[12]\\d|3[01])");

    if (!std::regex_search(line, date_pattern)) {
        throw BitcoinExchange::BE(
            "Did not found the date at the begining of the string");
    }

    int year = 0;
    try {
        year = std::stoi(line.substr(0, 4));
    } catch (std::invalid_argument &) {
        throw BitcoinExchange::BE("Invalid int for year");
    } catch (std::out_of_range &) {
        throw BitcoinExchange::BE("Invalid int (out of range) for year");
    } catch (...) {
        throw std::runtime_error(
            "Unknown error occurred while validate the data");
    }

    int month = 0;
    try {
        month = std::stoi(line.substr(5, 2));
    } catch (std::invalid_argument &) {
        throw BitcoinExchange::BE("Invalid int for month");
    } catch (std::out_of_range &) {
        throw BitcoinExchange::BE("Invalid int (out of range) for month");
    } catch (...) {
        throw std::runtime_error(
            "Unknown error occurred while validate the data");
    }

    int day = 0;
    try {
        day = std::stoi(line.substr(8, 2));
    } catch (std::invalid_argument &) {
        throw BitcoinExchange::BE("Invalid int for day");
    } catch (std::out_of_range &) {
        throw BitcoinExchange::BE("Invalid int (out of range) for day");
    } catch (...) {
        throw std::runtime_error(
            "Unknown error occurred while validate the data");
    }

    if (month < 1 || month > 12) {
        throw BitcoinExchange::BE(
            "Invalid month should be between 1 and 12 got: '" +
            std::to_string(month) + "'");
    }

    if (day < 1 || day > 31) {
        throw BitcoinExchange::BE(
            "Invalid day should be between 1 and 31 got: '" +
            std::to_string(day) + "'");
    }

    const std::vector<int> daysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2) {
        bool isLeapYear =
            (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeapYear ? 29 : 28)) {
            throw BitcoinExchange::BE("The year: '" + std::to_string(year) +
                                      "' is not a leap year");
        }
    } else if (day > daysInMonth[month - 1]) {
        throw BitcoinExchange::BE("The day: '" + std::to_string(day) +
                                  "' is not a valid day in month: '" +
                                  std::to_string(month) + "'");
    }
}

void BitcoinExchange::_checkDB(const ExchangeDay &ed) {
    try {
        double exchangePrice = _db.at(ed.date);
        std::cout << ed.date << " => " << ed.value << " = "
                  << exchangePrice * ed.value << '\n';
        return;
    } catch (const std::out_of_range &) {
        if (_fd.isEof() == true) {
            const auto &last = *_db.crbegin();
            std::cout << ed.date << " ==> " << ed.value << " = "
                      << last.second * ed.value << '\n';
            return;
        }

        ExchangeDay dbED;
        while (_fd.isEof() != true) {
            try {
                std::string targetValue = _fd.gnl();
                dbED = _getExchangeData(targetValue, _dbSeperator);
                _db[dbED.date] = dbED.value;

                if (dbED.date == ed.date) {
                    std::cout << ed.date << " => " << ed.value << " = "
                              << dbED.value * ed.value << '\n';
                    return;
                }

                if (dbED.date > ed.date) {
                    std::pair<std::string, double> last = _findClosest(ed.date);
                    std::cout << ed.date << " " << last.first << " ==> "
                              << ed.value << " = " << last.second * ed.value
                              << '\n';
                    return;
                }

            } catch (FileHandler::FileError &) {
                throw;
            } catch (BitcoinExchange::BE &) {
                throw;
            } catch (FileHandler::FileEOF &) {
                break;
            }
        }
    }

    std::pair<std::string, double> last = _findClosest(ed.date);
    std::cout << ed.date << " " << last.first << " => " << ed.value << " = "
              << last.second * ed.value << '\n';
}

std::pair<std::string, double>
BitcoinExchange::_findClosest(const std::string &target_date) {
    auto it = _db.upper_bound(target_date);

    if (it == _db.begin()) {
        return *it;
    }

    --it;
    return *it;
}

// Custom exceptions
BitcoinExchange::BE::BE(const std::string &msg) : std::runtime_error(msg) {
}
