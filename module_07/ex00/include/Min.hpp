/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Min.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/22 19:22:09 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/23 18:13:04 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MIN_HPP
#define MIN_HPP

template <typename T>
T min(T &a, T &b) {
    if (a < b) {
        return a;
    }

    return b;
};

#endif // !MIN_HPP
