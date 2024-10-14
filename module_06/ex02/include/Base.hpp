/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Base.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 19:54:31 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/14 19:55:28 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_HPP
#define BASE_HPP

#include <iostream>

class Base {
  public:
    Base();

    Base(const Base &rhs) = delete;
    Base &operator=(const Base &rhs) = delete;

    Base(Base &&rhs) noexcept = delete;
    Base &operator=(Base &&rhs) noexcept;

    virtual ~Base();
};

#endif // !BASE_HPP
