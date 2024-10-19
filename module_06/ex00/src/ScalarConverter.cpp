/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ScalarConverter.cpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 20:22:08 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/19 22:13:04 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ScalarConverter.hpp"

void ScalarConverter::convert(const std::string &data) {
    std::cout << std::fixed << std::setprecision(2);

    toChar(data);
    toInt(data);
    toFloat(data);
    toDouble(data);
}

void ScalarConverter::toChar(const std::string &data) {
    try {
        int c;
        if (data.length() == 1 && !std::isdigit(data[0])) {
            c = static_cast<int>(data[0]);
        } else {
            c = std::stoi(data);
        }

        if (c < 0 || c > 127) {
            std::cout << "char: impossible" << '\n';
        } else if (c < 32 || c == 127) {
            std::cout << "char: Non displayable" << '\n';
        } else {
            std::cout << "char: '" << static_cast<char>(c) << "'" << '\n';
        }
    } catch (const std::invalid_argument &) {
        std::cout << "char: impossible" << '\n';
    } catch (const std::out_of_range &) {
        std::cout << "char: impossible" << '\n';
    }
}

void ScalarConverter::toInt(const std::string &data) {
    try {
        size_t pos;
        double temp = std::stod(data, &pos);

        if (pos < data.length() && (data[pos] == 'f' || data[pos] == 'F')) {
            pos++;
        }

        if (pos != data.length()) {
            std::cout << "int: impossible" << '\n';
        } else if (temp > std::numeric_limits<int>::max() ||
                   temp < std::numeric_limits<int>::min() || std::isnan(temp) ||
                   std::isinf(temp)) {
            std::cout << "int: impossible" << '\n';
        } else {
            auto result = static_cast<int>(temp);
            std::cout << "int: " << result << '\n';
        }
    } catch (const std::invalid_argument &e) {
        std::cout << "int: impossible" << '\n';
    } catch (const std::out_of_range &e) {
        std::cout << "int: impossible" << '\n';
    }
}

// void ScalarConverter::toFloat(const std::string &data) {
//     try {
//         size_t pos;
//         float result;
//
//         if (data == "nan" || data == "nanf") {
//             result = std::numeric_limits<float>::quiet_NaN();
//             pos = data.length();
//         } else if (data == "+inf" || data == "inf" || data == "+inff" ||
//                    data == "inff") {
//             result = std::numeric_limits<float>::infinity();
//             pos = data.length();
//         } else if (data == "-inf" || data == "-inff") {
//             result = -std::numeric_limits<float>::infinity();
//             pos = data.length();
//         } else {
//             result = std::stof(data, &pos);
//             if (pos < data.length() && (data[pos] == 'f' || data[pos] ==
//             'F')) {
//                 pos++;
//             }
//         }
//
//         if (pos != data.length()) {
//             std::cout << "float: impossible" << '\n';
//         } else {
//             std::cout << "float: " << result << "f" << '\n';
//         }
//     } catch (const std::invalid_argument &e) {
//         std::cout << "float: impossible" << '\n';
//     } catch (const std::out_of_range &e) {
//         std::cout << "float: impossible" << '\n';
//     }
// }

void ScalarConverter::toFloat(const std::string &data) {
    try {
        size_t pos;
        double temp = std::stod(data, &pos);
        float result;

        if (data == "nan" || data == "nanf") {
            result = std::numeric_limits<float>::quiet_NaN();
        } else if (data == "+inf" || data == "inf" || data == "+inff" ||
                   data == "inff") {
            result = std::numeric_limits<float>::infinity();
        } else if (data == "-inf" || data == "-inff") {
            result = -std::numeric_limits<float>::infinity();
        } else if (std::abs(temp) < std::numeric_limits<float>::min() &&
                   temp != 0.0) {
            result = 0.0f;
        } else if (std::abs(temp) > std::numeric_limits<float>::max()) {
            result =
                std::copysign(std::numeric_limits<float>::infinity(), temp);
        } else {
            result = static_cast<float>(temp);
        }

        std::cout << "float: ";
        if (std::isnan(result)) {
            std::cout << "nanf" << '\n';
        } else if (std::isinf(result)) {
            std::cout << (result > 0 ? "inff" : "-inff") << '\n';
        } else {
            if (result == 0.0f) {
                std::cout << (std::signbit(temp) ? "-0.00f" : "0.00f") << '\n';
            } else {
                std::cout << result << "f" << '\n';
            }
        }
    } catch (const std::exception &e) {
        std::cout << "float: impossible" << '\n';
    }
}

void ScalarConverter::toDouble(const std::string &data) {
    try {
        size_t pos;
        double result;

        if (data == "nan" || data == "nanf") {
            result = std::numeric_limits<double>::quiet_NaN();
            pos = data.length();
        } else if (data == "+inf" || data == "inf" || data == "+inff" ||
                   data == "inff") {
            result = std::numeric_limits<double>::infinity();
            pos = data.length();
        } else if (data == "-inf" || data == "-inff") {
            result = -std::numeric_limits<double>::infinity();
            pos = data.length();
        } else {
            result = std::stod(data, &pos);
            if (pos < data.length() && (data[pos] == 'f' || data[pos] == 'F')) {
                pos++;
            }
        }

        if (pos != data.length() && data != "nanf" && data != "inff" &&
            data != "+inff" && data != "-inff") {
            std::cout << "double: impossible" << '\n';
        } else {
            std::cout << "double: " << result << '\n';
        }
    } catch (const std::invalid_argument &e) {
        std::cout << "double: impossible" << '\n';
    } catch (const std::out_of_range &e) {
        std::cout << "double: impossible" << '\n';
    }
}
