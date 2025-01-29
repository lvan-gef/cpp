#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <fstream>

class FileHandler {
  public:
    FileHandler();
    explicit FileHandler(std::string fname);

    FileHandler(const FileHandler &rhs) = delete;
    FileHandler &operator=(const FileHandler &rhs) = delete;

    FileHandler(FileHandler &&rhs) noexcept;
    FileHandler &operator=(FileHandler &&rhs) noexcept;

    ~FileHandler();

  public:
    void gnl(std::string &buffer);
    bool isEof() const;
    const std::string &getFilename() const;

  public:
    class FileEOF : public std::runtime_error {
      public:
        explicit FileEOF(const std::string &msg);
    };

    class FileError : public std::runtime_error {
      public:
        explicit FileError(const std::string &msg);
    };

  private:
    std::fstream _file;
    std::string _filename;
};

#endif // !FILEHANDLER_HPP
