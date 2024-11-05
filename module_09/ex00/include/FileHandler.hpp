#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

class FileHandler {
  public:
    FileHandler();
    explicit FileHandler(std::string fname);

    FileHandler(const FileHandler &rhs) = delete;
    FileHandler &operator=(const FileHandler &rhs) = delete;

    FileHandler(FileHandler &&rhs) noexcept;
    FileHandler &operator=(FileHandler &&rhs) noexcept;

    std::string gnl();
    bool isEof() const;

    std::string getFilename() const;
    class FileEOF : public std::runtime_error {
    public:
        explicit FileEOF(const std::string& msg);
    };

    class FileError : public std::runtime_error {
    public:
        explicit FileError(const std::string& msg);
    };

    ~FileHandler();

  private:
    std::fstream _file;
    std::string _filename;
    bool _isReading;
};

#endif // !FILEHANDLER_HPP
