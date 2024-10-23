/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Max.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/22 19:22:03 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/23 17:52:43 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAX_HPP
#define MAX_HPP

template <typename T>
T max(T &a, T &b) {
    if (a > b) {
        return a;
    }

    return b;
};

#endif // !MAX_HPP
