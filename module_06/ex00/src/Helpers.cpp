/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Helpers.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/21 18:20:51 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/22 00:23:49 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Helpers.hpp"

ScalarType detectType(const std::string &data) {
    if (data.length() == 1 && !std::isdigit(data[0])) {
        return ScalarType::CHAR;
    }

    if (data == "nanf" || data == "+inff" || data == "-inff" ||
        data == "inff") {
        return ScalarType::FLOAT;
    }

    if (data == "nan" || data == "+inf" || data == "-inf" || data == "inf") {
        return ScalarType::DOUBLE;
    }

    bool hasDecimal = false;
    bool hasFloat = false;
    bool hasScientific = false;

    for (size_t i = 0; i < data.length(); ++i) {
        if (i == 0 && (data[i] == '-' || data[i] == '+')) {
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

    if (hasScientific) {
        return ScalarType::DOUBLE;
    }
    if (hasFloat && !hasDecimal) {
        return ScalarType::INVALID;
    }

    if (hasFloat) {
        return ScalarType::FLOAT;
    }

    if (hasDecimal) {
        return ScalarType::DOUBLE;
    }

    return ScalarType::INT;
}

void toChar(const std::string &data) {
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

void toInt(const std::string &data) {
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

void toFloat(const std::string &data) {
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

void toDouble(const std::string &data) {
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

void printer(const std::string &data) {
    toChar(data);
    toInt(data);
    toFloat(data);
    toDouble(data);
}
