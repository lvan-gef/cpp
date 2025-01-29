#include "FileHandler.hpp"

FileHandler::FileHandler() : _file(""), _filename("") {
}

FileHandler::FileHandler(std::string fname) : _filename(std::move(fname)) {
    _file.open(_filename);

    if (!_file.is_open()) {
        throw FileHandler::FileError("File: '" + _filename +
                                     "' can't be opened");
    }
}

FileHandler::FileHandler(FileHandler &&rhs) noexcept
    : _filename(std::move(rhs._filename)) {
    _file.swap(rhs._file);
}

FileHandler &FileHandler::operator=(FileHandler &&rhs) noexcept {
    if (this != &rhs) {
        _filename = std::move(rhs._filename);
        _file.swap(rhs._file);
    }

    return *this;
}

void FileHandler::gnl(std::string &buffer) {
    if (_file.is_open() != true) {
        throw FileHandler::FileError("File: '" + _filename +
                                     "' is not open...");
    }

    buffer.clear();
    if (!std::getline(_file, buffer)) {
        if (_file.eof()) {
            throw FileHandler::FileEOF("");
        }
        throw FileHandler::FileError("Failed to read line");
    }
}

bool FileHandler::isEof() const {
    return _file.eof();
}

const std::string &FileHandler::getFilename() const {
    return _filename;
}

FileHandler::~FileHandler() {
    if (_file.is_open()) {
        _file.close();
    }
}

FileHandler::FileEOF::FileEOF(const std::string &msg)
    : std::runtime_error(msg) {
}
FileHandler::FileError::FileError(const std::string &msg)
    : std::runtime_error(msg) {
}
