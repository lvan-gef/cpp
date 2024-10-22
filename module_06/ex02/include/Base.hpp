/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Base.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 19:54:31 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/22 17:47:42 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_HPP
#define BASE_HPP

#include <chrono>
#include <iostream>
#include <random>

class A; // forward declaration
class B; // forward declaration
class C; // forward declaration

class Base {
  public:
    Base();

    Base(const Base &rhs) = delete;
    Base &operator=(const Base &rhs) = delete;

    Base(Base &&rhs) noexcept = delete;
    Base &operator=(Base &&rhs) noexcept;

    virtual ~Base();
};

Base *generate();
void identify(Base *p);
void identify(Base &p);

#endif // !BASE_HPP
