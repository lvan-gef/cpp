/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ScalarConverter.cpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 20:22:08 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/15 21:29:01 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ScalarConverter.hpp"

void ScalarConverter::convert(const std::string &data) {
    ScalarType type = ScalarConverter::detectType(data);

    if (type == ScalarType::INVALID) {
        std::cout << "Invalid input" << std::endl;
        return;
    }

    std::cout << std::fixed << std::setprecision(1);

    if (type == ScalarType::CHAR) {
        std::cout << "char: '" << data[1] << "'" << std::endl;
        std::cout << "int: " << static_cast<int>(data[1]) << std::endl;
        std::cout << "float: " << static_cast<float>(data[1]) << "f"
                  << std::endl;
        std::cout << "double: " << static_cast<double>(data[1]) << std::endl;
        return;
    }

    double dValue = NAN;
    long int iValue = NAN;
    if (type == ScalarType::INT) {
        iValue = std::stol(data);
        dValue = iValue;
    } else if (type == ScalarType::FLOAT) {
        dValue = std::stof(data);
        iValue = dValue;
    } else {
        dValue = std::stod(data);
        iValue = dValue;
    }

    // Char
    if (iValue >= 32 && iValue <= 126) {
        std::cout << "char: '" << static_cast<char>(iValue) << "'" << std::endl;
    } else {
        std::cout << "char: Non displayable" << std::endl;
    }

    // Int
    if (iValue > std::numeric_limits<int>::max() ||
        iValue < std::numeric_limits<int>::min() || std::isnan(iValue)) {
        std::cout << "int: impossible" << std::endl;
    } else {
        std::cout << "int: " << static_cast<int>(iValue) << std::endl;
    }

    // Float
    std::cout << "float: " << static_cast<float>(dValue) << "f" << std::endl;

    // Double
    std::cout << "double: " << static_cast<double>(dValue) << std::endl;
}

ScalarConverter::ScalarType
ScalarConverter::detectType(const std::string &data) {
    if (data.length() == 3 && data[0] == '\'' && data[2] == '\'') {
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
