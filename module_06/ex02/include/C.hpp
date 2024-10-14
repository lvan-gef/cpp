/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   C.hpp                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 19:54:32 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/14 19:54:32 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef C_HPP
#define C_HPP

#include "./Base.hpp"
#include <iostream>

class C : public Base {
  public:
    C() = default;

    C(const C &) = delete;
    C &operator=(const C &) = delete;

    C(C &&) noexcept = delete;
    C &operator=(C &&) noexcept = delete;

    ~C() override;
};

#endif // !C_HPP
