/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Fixed.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 23:12:22 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/02/03 23:18:14 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Fixed.hpp"

Fixed::Fixed() : value(0) { std::cout << "Default constructor called\n"; }

Fixed::Fixed(const Fixed &fixed) : value(fixed.value) {
  std::cout << "Copy constructor called\n";
}

Fixed &Fixed::operator=(const Fixed &fixed) {
  std::cout << "Copy assigment operator called\n";
  if (this != &fixed) {
    this->value = fixed.value;
  }

  return *this;
}

int Fixed::getRawBits(void) const {
  std::cout << "getRawBits member function called\n";
  return this->value;
}

void Fixed::setRawBits(int const raw) {
  std::cout << "setRawBits member function called\n";
  this->value = raw;
}

Fixed::~Fixed() { std::cout << "Destructor called\n"; }
