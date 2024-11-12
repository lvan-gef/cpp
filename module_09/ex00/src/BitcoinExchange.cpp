#include "../include/BitcoinExchange.hpp"

ExchangeDay::ExchangeDay(ExchangeDay &&other) noexcept
    : date(std::move(other.date)), value(other.value) {
}

ExchangeDay &ExchangeDay::operator=(ExchangeDay &&other) noexcept {
    if (this != &other) {
        date = std::move(other.date);
        value = other.value;
    }
    return *this;
}

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
            targetED =
                _getExchangeData(std::move(targetValue), _targetSeperator);
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
    const int headerSize = 5;
    const uint8_t startSize = 4;
    std::string header;
    std::ostringstream oss;

    try {
        header = fh.gnl();
    } catch (FileHandler::FileEOF &e) {
        throw BitcoinExchange::BE(e.what());
    } catch (FileHandler::FileError &e) {
        throw BitcoinExchange::BE(e.what());
    }

    if (_startsWith(header) != true) {
        oss << "First line of '" << fh.getFilename()
            << "' must start with: 'date'";
        throw BitcoinExchange::BE(oss.str());
    }

    char nextChar = header[startSize];
    if (nextChar == ' ' && header.length() >= headerSize) {
        nextChar = header[startSize + 1];
    }

    std::vector<std::string> validSeparators = {",", ";", "\t", "|", " "};
    auto it = std::find_if(validSeparators.begin(), validSeparators.end(),
                           [nextChar](const std::string &sep) {
                               return !sep.empty() && sep[0] == nextChar;
                           });
    if (it == validSeparators.end()) {
        oss << "Could not found a valid separator '" << fh.getFilename() << "'";
        throw BitcoinExchange::BE(oss.str());
    }

    return *it;
}

ExchangeDay BitcoinExchange::_getExchangeData(std::string line,
                                              const std::string &separator) {
    std::vector<std::string> tokens;
    tokens.reserve(2);
    size_t pos = 0;
    size_t prev = 0;
    std::ostringstream oss;

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

    size_t start = line.find_first_not_of(" \t", prev);
    size_t end = line.find_last_not_of(" \t");
    if (start != std::string::npos && end != std::string::npos) {
        tokens.emplace_back(line.substr(start, end - start + 1));
    }

    if (tokens.size() != 2) {
        oss << "Invalid format for input: '" << line << "', expected 2 '"
            << separator
            << "' separated values, got: " << std::to_string(tokens.size());
        throw BitcoinExchange::BE(oss.str());
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
            oss << ed.date << " value must be more then 0.0 and less then "
                << std::to_string(_maxValue) << "  got: '"
                << std::to_string(ed.value) << "'";
            throw BitcoinExchange::BE(oss.str());
        } else if (ed.value < 0) {
            oss << "value must be more then 0.0 got: '"
                << std::to_string(ed.value) << "'";
            throw BitcoinExchange::BE(oss.str());
        }
    } catch (std::invalid_argument &e) {
        oss << "value: '" << tokens[1] << "' is not a valid float... ("
            << e.what() << ")";
        throw BitcoinExchange::BE(oss.str());
    } catch (std::out_of_range &) {
        throw BitcoinExchange::BE("Invalid float (out of range) for value");
    }

    return ed;
}

void BitcoinExchange::_validateDate(const std::string &line) {
    std::ostringstream oss;
    if (line.length() != 10 || line[4] != '-' || line[7] != '-') {
        throw BitcoinExchange::BE("Invalid line format");
    }

    int year = std::stoi(line.substr(0, 4));
    int month = std::stoi(line.substr(5, 2));
    int day = std::stoi(line.substr(8, 2));

    try {
        year = (line[0] - '0') * 1000 + (line[1] - '0') * 100 +
               (line[2] - '0') * 10 + (line[3] - '0');
    } catch (...) {
        throw BitcoinExchange::BE("Invalid year format");
    }

    if (month < 1 || month > 12) {
        oss << "Invalid month should be between 1 and 12 got: '"
            << std::to_string(month) << "'";
        throw BitcoinExchange::BE(oss.str());
    }

    if (day < 1 || day > 31) {
        oss << "Invalid day should be between 1 and 31 got: '"
            << std::to_string(day) << "'";
        throw BitcoinExchange::BE(oss.str());
    }

    static const std::vector<int> daysInMonth = {31, 28, 31, 30, 31, 30,
                                                 31, 31, 30, 31, 30, 31};
    if (month == 2) {
        bool isLeapYear =
            (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
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
            ExchangeDay dbED =
                _getExchangeData(std::move(targetValue), _dbSeperator);
            _db.emplace(std::move(dbED.date), dbED.value);
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
