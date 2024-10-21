/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ScalarConverter.cpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 20:22:08 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/21 19:43:08 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ScalarConverter.hpp"

void ScalarConverter::convert(const std::string &data) {
    std::cout << std::fixed << std::setprecision(2);

    ScalarType type = detectType(data);

    switch (type) {
        case ScalarType::CHAR:
            printer(data);
            break;
        case ScalarType::INT:
            printer(data);
            break;
        case ScalarType::FLOAT:
            printer(data);
            break;
        case ScalarType::DOUBLE:
            printer(data);
            break;;
        case ScalarType::INVALID:
            std::cerr << "Invalid\n";
            std::cout << "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible" << '\n';
    }
}
