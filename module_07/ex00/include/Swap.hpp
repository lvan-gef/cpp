/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Swap.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/22 19:22:19 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/22 19:22:20 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SWAP_HPP
#define SWAP_HPP

template <typename T> void swap(T &a, T &b) { (a ^= b), (b ^= a), (a ^= b); }

#endif // !SWAP_HPP
