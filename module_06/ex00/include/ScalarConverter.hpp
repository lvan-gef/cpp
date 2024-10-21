/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ScalarConverter.hpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 20:21:57 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/21 18:10:06 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iomanip>

#include "./Helpers.hpp"

class ScalarConverter {
  public:
    ScalarConverter() = delete;
    ScalarConverter(const ScalarConverter &rhs) = delete;
    ScalarConverter &operator=(const ScalarConverter &rhs) = delete;

    ScalarConverter(ScalarConverter &&rhs) noexcept = delete;
    ScalarConverter &operator=(ScalarConverter &&rhs) noexcept = delete;

    static void convert(const std::string &data);
    ~ScalarConverter() = delete;
};

#endif // !SCALARCONVERTER_HPP
