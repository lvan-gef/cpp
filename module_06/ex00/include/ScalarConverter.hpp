/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ScalarConverter.hpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 20:21:57 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/17 19:37:24 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

class ScalarConverter {
  public:
    ScalarConverter() = delete;
    ScalarConverter(const ScalarConverter &rhs) = delete;
    ScalarConverter &operator=(const ScalarConverter &rhs) = delete;

    ScalarConverter(ScalarConverter &&rhs) noexcept = delete;
    ScalarConverter &operator=(ScalarConverter &&rhs) noexcept = delete;

    static void convert(const std::string &data);
    ~ScalarConverter() = delete;

  private:
    enum class ScalarType { CHAR, INT, FLOAT, DOUBLE, INVALID };
    static ScalarType detectType(const std::string &data);
    static void toChar(long int c);
    static void toInt(long int c);
};

#endif // !SCALARCONVERTER_HPP
