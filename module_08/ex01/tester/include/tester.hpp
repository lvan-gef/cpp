/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 18:45:04 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/11/02 18:38:40 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_HPP
#define TESTER_HPP

#include <iostream>
#include <random>
#include <vector>
#include <chrono>

#include "../../include/Span.hpp"

void span_tester();
std::vector<int> randomVector(unsigned int N);
void printer(std::vector<int> data);

#endif // TESTER_HPP
