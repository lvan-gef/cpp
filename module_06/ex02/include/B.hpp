/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   B.hpp                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 19:54:31 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/14 19:55:07 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef B_HPP
#define B_HPP

#include "./Base.hpp"
#include <iostream>

class B : public Base {
  public:
    B() = default;

    B(const B &) = delete;
    B &operator=(const B &) = delete;

    B(B &&) noexcept = delete;
    B &operator=(B &&) noexcept = delete;

    ~B() override;
};

#endif // !B_HPP
