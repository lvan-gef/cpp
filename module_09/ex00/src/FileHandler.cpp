#include "../include/FileHandler.hpp"
#include <stdexcept>

FileHandler::FileHandler(std::string fname) : _filename(std::move(fname)) {}

ExchangeData FileHandler::gnl() {
    ExchangeData ed;
    if (!_file.is_open()) {
        throw std::runtime_error("File is not open...");
    }

    std::string line;
    std::vector<std::string> data;

    if (std::getline(_file, line, ',')) {
        data.push_back(line);
        if (data.size() != 2) {
            throw std::out_of_range("Invalid format, must be ',' seperated");
        }
        ed.date = data[0];
        ed.value = 1.1;
    } else {
        throw std::runtime_error("Failed to get a new line");
    }

    return ed;
}

bool FileHandler::isEof() const {
    return _file.eof();
}

FileHandler::~FileHandler() {
    if (_file.is_open()) {
        _file.close();
    }
}
