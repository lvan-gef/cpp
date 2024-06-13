/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 23:12:46 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 22:22:39 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <iostream>

#include "../include/Fixed.hpp"

int main() {
    std::cout << "Test default constructor\n";
    Fixed a;
    assert(a.getRawBits() == 0);

    std::cout << "\nTest Copy constructor\n";
    Fixed d(a);
    assert(d.getRawBits() == 0);

    std::cout << "\nTest Copy Assignment operator\n";
    Fixed e;
    e = d;
    assert(e.getRawBits() == 0);

    std::cout << "\nTest Copy Assignment operator to it self\n";
    e.setRawBits(1);
    e = e;
    assert(e.getRawBits() == 1);

    Fixed f;
    std::cout << "\nTest setRawBits and getRawBits\n";
    f.setRawBits(256);
    assert(f.getRawBits() == 256);

    std::cout << "All tests passed successfully.\n" << std::endl;

    return 0;
}
