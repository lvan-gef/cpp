#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <stdexcept>
#include <vector>

struct ExchangeData {
    std::string date;
    float value;
};

class FileHandler {
  public:
    explicit FileHandler(std::string fname);

    FileHandler(const FileHandler &rhs) = delete;
    FileHandler &operator=(const FileHandler &rhs) = delete;

    FileHandler(FileHandler &&rhs) noexcept = delete;
    FileHandler &operator=(FileHandler &&rhs) noexcept = delete;

    bool isEof() const;
    ExchangeData gnl();

    ~FileHandler();

  private:
    std::fstream _file;
    std::string _filename;
};

#endif // !FILEHANDLER_HPP
