/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ScalarConverter.cpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 20:22:08 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/17 19:39:59 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ScalarConverter.hpp"
#include <string>

void ScalarConverter::convert(const std::string &data) {
    ScalarType type = ScalarConverter::detectType(data);

    std::cout << std::fixed << std::setprecision(2);

    if (type == ScalarType::CHAR) {
        char c = data[0];
        toChar(c);
        toInt(c);
        std::cout << "float: " << static_cast<float>(c) << "f" << '\n';
        std::cout << "double: " << static_cast<double>(c) << '\n';
        return;
    }
    else if (type == ScalarType::INT) {
        long int value = std::stol(data);
        toChar(value);
        toInt(value);
        std::cout << "float: " << static_cast<float>(value) << "f" << '\n';
        std::cout << "double: " << static_cast<double>(value) << '\n';
    }

    // double dValue = NAN;
    // long int iValue = NAN;
    // if (type == ScalarType::INT) {
    //     iValue = std::stol(data);
    //     dValue = iValue;
    // } else if (type == ScalarType::FLOAT) {
    //     dValue = std::stof(data);
    //     iValue = dValue;
    // } else {
    //     dValue = std::stod(data);
    //     iValue = dValue;
    // }
    //
    // // Char
    // if (iValue >= 32 && iValue <= 126) {
    //     std::cout << "char: '" << static_cast<char>(iValue) << "'" <<
    //     std::endl;
    // } else {
    //     std::cout << "char: Non displayable" << std::endl;
    // }
    //
    // // Int
    // if (iValue > std::numeric_limits<int>::max() ||
    //     iValue < std::numeric_limits<int>::min() || std::isnan(iValue)) {
    //     std::cout << "int: impossible" << std::endl;
    // } else {
    //     std::cout << "int: " << static_cast<int>(iValue) << std::endl;
    // }
    //
    // // Float
    // std::cout << "float: " << static_cast<float>(dValue) << "f" << std::endl;
    //
    // // Double
    // std::cout << "double: " << static_cast<double>(dValue) << std::endl;
}

ScalarConverter::ScalarType
ScalarConverter::detectType(const std::string &data) {
    if (data.length() == 1 && static_cast<unsigned char>(data[0]) <= 127) {
        return ScalarType::CHAR;
    }

    if (data == "nanf" || data == "+inff" || data == "-inff") {
        return ScalarType::FLOAT;
    }

    if (data == "nan" || data == "+inf" || data == "-inf") {
        return ScalarType::DOUBLE;
    }

    bool hasDecimal = false;
    bool hasFloat = false;

    for (size_t i = 0; i < data.length(); ++i) {
        if (i == 0 && data[i] == '-') {
            continue;
        }

        if (data[i] == '.') {
            if (hasDecimal)
                return ScalarType::INVALID;
            hasDecimal = true;
        } else if (i == data.length() - 1 &&
                   (data[i] == 'f' || data[i] == 'F')) {
            hasFloat = true;
        } else if (!std::isdigit(data[i])) {
            return ScalarType::INVALID;
        }
    }

    if (hasFloat && !hasDecimal)
        return ScalarType::INVALID;
    if (hasFloat)
        return ScalarType::FLOAT;
    if (hasDecimal)
        return ScalarType::DOUBLE;

    return ScalarType::INT;
}

void ScalarConverter::toChar(long int c) {
    if (c < 32 || c > 126) {
        std::cout << "char: Non displayable" << '\n';
    } else {
        std::cout << "char: '" << static_cast<char>(c) << "'" << '\n';
    }
}

void ScalarConverter::toInt(long int c) {
    if (c > std::numeric_limits<int>::max() ||
        c < std::numeric_limits<int>::min() || std::isnan(c)) {
        std::cout << "int: impossible" << '\n';
    } else {
        std::cout << "int: " << static_cast<int>(c) << '\n';
    }
}
