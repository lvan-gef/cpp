/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Swap.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/22 19:22:19 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/23 18:23:17 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SWAP_HPP
#define SWAP_HPP

#include <utility>

template <typename T>
void swap(T &a, T &b) {
    T tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}

#endif // !SWAP_HPP
