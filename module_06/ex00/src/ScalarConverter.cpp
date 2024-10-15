/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ScalarConverter.cpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 20:22:08 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/15 16:53:04 by lvan-gef      ########   odam.nl         */
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

    double value = NAN;
    try {
        if (type == ScalarType::INT)
            value = std::stoi(data);
        else if (type == ScalarType::FLOAT)
            value = std::stof(data);
        else
            value = std::stod(data);

        // Char
        if (value >= 32 && value <= 126)
            std::cout << "char: '" << static_cast<char>(value) << "'"
                      << std::endl;
        else
            std::cout << "char: Non displayable" << std::endl;

        // Int
        if (value > std::numeric_limits<int>::max() ||
            value < std::numeric_limits<int>::min() || std::isnan(value))
            std::cout << "int: impossible" << std::endl;
        else
            std::cout << "int: " << static_cast<int>(value) << std::endl;

        // Float
        if (type == ScalarType::FLOAT)
            std::cout << "float: " << data << std::endl;
        else
            std::cout << "float: " << value << "f" << std::endl;

        // Double
        if (type == ScalarType::DOUBLE)
            std::cout << "double: " << data << std::endl;
        else
            std::cout << "double: " << value << std::endl;
    } catch (const std::exception &e) {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
    }
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
    bool hasF = false;

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
            hasF = true;
        } else if (!std::isdigit(data[i])) {
            return ScalarType::INVALID;
        }
    }

    if (hasF && !hasDecimal)
        return ScalarType::INVALID;
    if (hasF)
        return ScalarType::FLOAT;
    if (hasDecimal)
        return ScalarType::DOUBLE;

    return ScalarType::INT;
}
