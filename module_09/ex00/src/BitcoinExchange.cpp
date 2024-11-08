#include "../include/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string &file)
    : _fd(file), _maxValue(1000) {
    std::cout << std::fixed;
    std::cout.precision(2);

    try {
        _dbSeperator = _getSeperator(_fd);
        _loadDB();
    } catch (FileHandler::FileError &) {
        throw;
    } catch (FileHandler::FileEOF &) {
        return;
    } catch (BitcoinExchange::BE &) {
        throw;
    }
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
        _targetSeperator = _getSeperator(ft);
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

std::string BitcoinExchange::_getSeperator(FileHandler &fh) {
    std::string header;
    const int headerSize = 5;

    try {
        header = fh.gnl();
    } catch (FileHandler::FileEOF &e) {
        throw BitcoinExchange::BE(e.what());
    } catch (FileHandler::FileError &e) {
        throw BitcoinExchange::BE(e.what());
    }

    const uint8_t startSize = 4;
    char nextChar = header[startSize];

    if (_startsWith(header) != true) {
        throw BitcoinExchange::BE("First line of '" + fh.getFilename() +
                                  "' must start with: 'date'");
    }

    if (nextChar == ' ' && header.length() >= headerSize) {
        nextChar = header[startSize + 1];
    }

    std::vector<std::string> validSeparators = {",", ";", "\t", "|", " "};
    auto it = std::find_if(validSeparators.begin(), validSeparators.end(),
                           [nextChar](const std::string &sep) {
                               return !sep.empty() && sep[0] == nextChar;
                           });
    if (it == validSeparators.end()) {
        throw BitcoinExchange::BE("Could not found a valid separator for " +
                                  fh.getFilename());
    }

    return *it;
}

ExchangeDay BitcoinExchange::_getExchangeData(const std::string &line, const std::string &separator) {
    std::vector<std::string> tokens;
    tokens.reserve(2);

    size_t pos = 0;
    size_t prev = 0;

    while ((pos = line.find(separator[0], prev)) != std::string::npos) {
        if (pos > prev) {
            size_t start = line.find_first_not_of(" \t", prev);
            size_t end = line.find_last_not_of(" \t", pos - 1);
            if (start != std::string::npos && end != std::string::npos) {
                tokens.emplace_back(line.substr(start, end - start + 1));
            }
        }
        prev = pos + 1;
    }

    // Get last token
    size_t start = line.find_first_not_of(" \t", prev);
    size_t end = line.find_last_not_of(" \t");
    if (start != std::string::npos && end != std::string::npos) {
        tokens.emplace_back(line.substr(start, end - start + 1));
    }

    if (tokens.size() != 2) {
        throw BitcoinExchange::BE(
            "Invalid format for input: '" + line + "', expected 2 '" +
            separator + "' separated values, got: " + std::to_string(tokens.size()));
    }

    ExchangeDay ed;
    try {
        _validateDate(tokens[0]);
        ed.date = std::move(tokens[0]);
    } catch (BitcoinExchange::BE &) {
        throw;
    }

    try {
        ed.value = std::stof(tokens[1]);
        if (ed.value > _maxValue) {
            throw BitcoinExchange::BE(
                ed.date + " value must be more then 0.0 and less then " +
                std::to_string(_maxValue) + "  got: '" +
                std::to_string(ed.value) + "'");
        } else if (ed.value < 0) {
            throw BitcoinExchange::BE("value must be more then 0.0 got: '" +
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

void BitcoinExchange::_validateDate(const std::string &line) {
    static const std::regex date_pattern(
        "^\\d{4}-(?:0[1-9]|1[0-2])-(?:0[1-9]|[12]\\d|3[01])");

    if (!std::regex_search(line, date_pattern)) {
        throw BitcoinExchange::BE(
            "Did not found the date at the begining of the string");
    }

    // Direct character access instead of substr
    int year = 0;
    try {
        year = (line[0] - '0') * 1000 + (line[1] - '0') * 100 +
               (line[2] - '0') * 10 + (line[3] - '0');
    } catch (...) {
        throw BitcoinExchange::BE("Invalid year format");
    }

    int month = (line[5] - '0') * 10 + (line[6] - '0');
    if (month < 1 || month > 12) {
        throw BitcoinExchange::BE(
            "Invalid month should be between 1 and 12 got: '" +
            std::to_string(month) + "'");
    }

    int day = (line[8] - '0') * 10 + (line[9] - '0');
    if (day < 1 || day > 31) {
        throw BitcoinExchange::BE(
            "Invalid day should be between 1 and 31 got: '" +
            std::to_string(day) + "'");
    }

    static const std::vector<int> daysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeapYear ? 29 : 28)) {
            throw BitcoinExchange::BE("Invalid day for February");
        }
    } else if (day > daysInMonth[month - 1]) {
        throw BitcoinExchange::BE("Invalid day for given month");
    }
}

void BitcoinExchange::_loadDB() {
    while (_fd.isEof() != true) {
        try {
            std::string targetValue = _fd.gnl();
            ExchangeDay dbED = _getExchangeData(targetValue, _dbSeperator);
            _db[dbED.date] = dbED.value;
        } catch (FileHandler::FileError &) {
            throw;
        } catch (BitcoinExchange::BE &e) {
            continue;
        } catch (FileHandler::FileEOF &) {
            break;
        }
    }
}

void BitcoinExchange::_checkDB(const ExchangeDay &ed) {
    if (_db.size() == 0) {
        throw BitcoinExchange::BE("DB is empty...");
    }

    try {
        float exchangePrice = _db.at(ed.date);
        std::cout << ed.date << " => " << ed.value << " = "
                  << exchangePrice * ed.value << '\n';
        return;
    } catch (const std::out_of_range &) {
        try {
            const float value = _findClosest(ed.date);
            std::cout << ed.date << " => " << ed.value << " = "
                      << value * ed.value << '\n';
            return;
        } catch (BitcoinExchange::BE &) {
            throw;
        }
    }
}

float BitcoinExchange::_findClosest(const std::string &target_date) {
    auto it = _db.upper_bound(target_date);

    if (it == _db.begin()) {
        if (target_date < it->first) {
            throw BitcoinExchange::BE(
                "Date lower then the lowest date in the data set");
        }
        return it->second;
    }

    --it;

    return it->second;
}

// Custom exceptions
BitcoinExchange::BE::BE(const std::string &msg) : std::runtime_error(msg) {
}

BitcoinExchange::OutOfRange::OutOfRange(const std::string &msg)
    : std::runtime_error(msg) {
}
