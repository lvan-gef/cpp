/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Helpers.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/21 18:03:58 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/21 19:58:29 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <cmath>
#include <iostream>
#include <limits>

enum class ScalarType { CHAR, INT, FLOAT, DOUBLE, INVALID };
ScalarType detectType(const std::string &data);
void toChar(const std::string &data);
void toInt(const std::string &data);
void toFloat(const std::string &data);
void toDouble(const std::string &data);
void printer(const std::string &data);

#endif // !HELPERS_HPP
