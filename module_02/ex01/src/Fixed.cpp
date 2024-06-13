/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Fixed.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 23:12:46 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/02/03 23:24:02 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Fixed.hpp"

Fixed::Fixed() : value(0) { std::cout << "Default constructor called\n"; }

Fixed::Fixed(const int &number) : value(roundf(number * (1 << fraction))) {
  std::cout << "Int constructor called\n";
}

Fixed::Fixed(const float &number)
    : value(static_cast<int>(roundf(number * (1 << fraction)))) {
  std::cout << "Float constructor called\n";
}

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

int Fixed::toInt(void) const { return value / static_cast<int>(1 << fraction); }

float Fixed::toFloat(void) const {
  return static_cast<float>(value) / static_cast<float>(1 << fraction);
}

int Fixed::getRawBits(void) const {
  std::cout << "getRawBits member function called\n";
  return value;
}

void Fixed::setRawBits(int const raw) {
  std::cout << "setRawBits member function called\n";
  value = raw;
}

Fixed::~Fixed() { std::cout << "Destructor called\n"; }

std::ostream &operator<<(std::ostream &os, const Fixed &fixed) {
  os << fixed.toFloat();
  return os;
}
