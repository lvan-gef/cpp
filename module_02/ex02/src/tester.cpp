/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 23:13:06 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 22:22:39 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <iostream>

#include "../include/Fixed.hpp"

int main() {
    Fixed a(5.5f);
    Fixed b(10.5f);
    Fixed x(5.5f);
    Fixed z(10.5f);

    std::cout << "Test Comparison operators\n";
    assert(a < b);
    assert(b > a);
    assert(a <= b);
    assert(a <= x);
    assert(b >= a);
    assert(b >= z);
    assert(a != b);
    assert(x == a);

    std::cout << "Test Arithmetic operators\n";
    Fixed c = a + b;
    Fixed d = b - a;
    Fixed e = a * Fixed(2);
    Fixed f = b / Fixed(2);

    assert(c.toFloat() == 16.0f);
    assert(d.toFloat() == 5.0f);
    assert(e.toFloat() == 11.0f);
    assert(f.toFloat() == 5.0f);
    assert(c.toInt() == 16);
    assert(d.toInt() == 5);
    assert(e.toInt() == 11);
    assert(f.toInt() == 5);

    std::cout << "Test Pre and Post operators\n";
    Fixed preInc = ++a; // Pre-increment
    assert(preInc.getRawBits() == a.getRawBits());

    Fixed postInc = b++; // Post-increment
    assert(b.getRawBits() - postInc.getRawBits() == 1);

    Fixed preDec = --a; // Pre-decrement
    assert(preDec.getRawBits() == a.getRawBits());

    Fixed postDec = b--; // Post-decrement
    assert(postDec.getRawBits() - b.getRawBits() == 1);

    std::cout << "Test Static min/max functions\n";
    Fixed const &minFixed = Fixed::min(a, b);
    assert(minFixed == a);

    Fixed const &maxFixed = Fixed::max(a, b);
    assert(maxFixed == b);

    std::cout << "Test Const min/max functions\n";
    const Fixed constA(5.5f);
    const Fixed constB(10.5f);

    const Fixed &minConstFixed = Fixed::min(constA, constB);
    assert(minConstFixed == constA);

    const Fixed &maxConstFixed = Fixed::max(constA, constB);
    assert(maxConstFixed == constB);

    return 0;
}
