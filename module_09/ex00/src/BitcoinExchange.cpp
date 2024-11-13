#include "../include/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string &file)
    : _fd(file), _maxValue(1000) {
    std::cout << std::fixed;
    std::cout.precision(2);

    try {
        _dbSeperator = _getSeperator(_fd);
        _loadDB();
        _lineBuffer.reserve(100);
        _tokenBuffer.reserve(2);
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
    _errorBuffer.str("");

    try {
        ft = FileHandler(file);
    } catch (FileHandler::FileError &e) {
        throw BitcoinExchange::BE(e.what());
    } catch (...) {
        _errorBuffer << "getResult: FileHandler: Unknown error";
        throw BitcoinExchange::BE(_errorBuffer.str());
    }

    try {
        _targetSeperator = _getSeperator(ft);
    } catch (BitcoinExchange::BE &) {
        throw;
    }

    ExchangeDay targetED;
    while (ft.isEof() != true) {
        try {
            _lineBuffer.clear();
            ft.gnl(_lineBuffer);
            targetED =
                _getExchangeData(_lineBuffer, _targetSeperator);
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
    _errorBuffer.str("");

    try {
        _lineBuffer.clear();
        fh.gnl(_lineBuffer);
    } catch (FileHandler::FileEOF &e) {
        throw BitcoinExchange::BE(e.what());
    } catch (FileHandler::FileError &e) {
        throw BitcoinExchange::BE(e.what());
    }

    if (_startsWith(_lineBuffer) != true) {
        _errorBuffer << "First line of '" << fh.getFilename()
            << "' must start with: 'date'";
        throw BitcoinExchange::BE(_errorBuffer.str());
    }

    char nextChar = _lineBuffer[startSize];
    if (nextChar == ' ' && _lineBuffer.length() >= headerSize) {
        nextChar = _lineBuffer[startSize + 1];
    }

    std::vector<std::string> validSeparators = {",", ";", "\t", "|", " "};
    auto it = std::find_if(validSeparators.begin(), validSeparators.end(),
                           [nextChar](const std::string &sep) {
                               return !sep.empty() && sep[0] == nextChar;
                           });
    if (it == validSeparators.end()) {
        _errorBuffer << "Could not found a valid separator '" << fh.getFilename() << "'";
        throw BitcoinExchange::BE(_errorBuffer.str());
    }

    return *it;
}

ExchangeDay BitcoinExchange::_getExchangeData(const std::string &line,
                                              const std::string &separator) {
    _tokenBuffer.clear();
    _errorBuffer.str("");
    size_t prev = 0;
    size_t pos = 0;

    while ((pos = line.find(separator[0], prev)) != std::string::npos) {
        if (pos > prev) {
            _tokenBuffer.push_back(line.substr(prev, pos - prev));
        }
        prev = pos + 1;
    }
    _tokenBuffer.push_back(line.substr(prev));

    if (_tokenBuffer.size() != 2) {
        _errorBuffer << "Invalid format: expected 2 values, got "
                     << _tokenBuffer.size();
        throw BitcoinExchange::BE(_errorBuffer.str());
    }

    ExchangeDay ed;
    try {
        trim(_tokenBuffer[0]);
        _validateDate(_tokenBuffer[0]);
        ed.date = std::move(_tokenBuffer[0]);
    } catch (BitcoinExchange::BE &) {
        throw;
    }

    try {
        ed.value = std::stof(_tokenBuffer[1]);
        if (ed.value < 0) {
            _errorBuffer << "value must be more then 0.0 got: '"
                << ed.value << "'";
            throw BitcoinExchange::BE(_errorBuffer.str());
        }
    } catch (std::invalid_argument &e) {
        _errorBuffer << "value: '" << _tokenBuffer[1] << "' is not a valid float... ("
            << e.what() << ")";
        throw BitcoinExchange::BE(_errorBuffer.str());
    } catch (std::out_of_range &) {
        throw BitcoinExchange::BE("Invalid float (out of range) for value");
    }

    return ed;
}

void BitcoinExchange::_validateDate(std::string &line) {
    _errorBuffer.str("");
    if (line.length() != 10 || line[4] != '-' || line[7] != '-') {
        throw BitcoinExchange::BE("Invalid line format");
    }


    int year;
    int month;
    int day;
    try {
        year = std::stoi(line.substr(0, 4));
        month = std::stoi(line.substr(5, 2));
        day = std::stoi(line.substr(8, 2));
    } catch (...) {
        throw BitcoinExchange::BE("Invalid date not all numbers");
    }

    if (month < 1 || month > 12) {
        _errorBuffer << "Invalid month should be between 1 and 12 got: '" << month << "'";
        throw BitcoinExchange::BE(_errorBuffer.str());
    }

    if (day < 1 || day > 31) {
        _errorBuffer << "Invalid day should be between 1 and 31 got: '" << day << "'";
        throw BitcoinExchange::BE(_errorBuffer.str());
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
    while (!_fd.isEof()) {
        try {
            _lineBuffer.clear();
            _fd.gnl(_lineBuffer);

            if (_lineBuffer.empty())
                continue;

            ExchangeDay dbED = _getExchangeData(_lineBuffer, _dbSeperator);
            _db.emplace(std::move(dbED.date), dbED.value);
        } catch (...) {
            continue;
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
