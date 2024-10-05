#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>


class ScalarConverter {
  public:
    ScalarConverter();

    ScalarConverter(const ScalarConverter &rhs) = delete;
    ScalarConverter &operator=(const ScalarConverter &rhs) = delete;

    ScalarConverter(ScalarConverter &&rhs) noexcept = delete;
    ScalarConverter &operator=(ScalarConverter &&rhs) noexcept = delete;

    static void convert(const std::string &data);

    ~ScalarConverter();

  private:
	enum class ScalarType { CHAR, INT, FLOAT, DOUBLE, INVALID };
    static ScalarType detectType(const std::string &data);
};

#endif // !SCALARCONVERTER_HPP
