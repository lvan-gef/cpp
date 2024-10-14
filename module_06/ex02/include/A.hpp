/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   A.hpp                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 19:54:31 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/14 19:54:31 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef A_HPP
#define A_HPP

#include "./Base.hpp"
#include <iostream>

class A : public Base {
  public:
    A() = default;

    A(const A &) = delete;
    A &operator=(const A &) = delete;

    A(A &&) noexcept = delete;
    A &operator=(A &&) noexcept = delete;

    ~A() override;
};

#endif // !A_HPP
