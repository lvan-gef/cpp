/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   easyfind.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 17:39:18 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/28 17:39:50 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <cassert>
#include <iostream>
#include <list>
#include <stdexcept>
#include <vector>

template <typename T>
void easyfind(T array, int target);

#include "../templates/easyfind.tpp"

#endif // !EASYFIND_HPP
