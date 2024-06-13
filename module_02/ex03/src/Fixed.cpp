/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Fixed.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 23:13:34 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 22:22:39 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Fixed.hpp"

Fixed::Fixed() : value(0) {}

Fixed::Fixed(const int &number) : value(roundf(number * (1 << fraction))) {}

Fixed::Fixed(const float &number)
    : value(static_cast<int>(roundf(number * (1 << fraction)))) {}

Fixed::Fixed(const Fixed &fixed) : value(fixed.value) {}

Fixed &Fixed::operator=(const Fixed &fixed) {
    if (this != &fixed) {
        this->value = fixed.value;
    }
    return *this;
}

bool Fixed::operator<(const Fixed &fixed) const {
    if (value < fixed.value) {
        return true;
    }
    return false;
}

bool Fixed::operator>(const Fixed &fixed) const {
    if (value > fixed.value) {
        return true;
    }
    return false;
}

bool Fixed::operator>=(const Fixed &fixed) const {
    if (value >= fixed.value) {
        return true;
    }
    return false;
}

bool Fixed::operator<=(const Fixed &fixed) const {
    if (value <= fixed.value) {
        return true;
    }
    return false;
}

bool Fixed::operator==(const Fixed &fixed) const {
    if (value == fixed.value) {
        return true;
    }
    return false;
}

bool Fixed::operator!=(const Fixed &fixed) const {
    if (value != fixed.value) {
        return true;
    }
    return false;
}

Fixed Fixed::operator+(const Fixed &fixed) {
    Fixed fix;

    fix.value = value + fixed.value;
    return fix;
}

Fixed Fixed::operator-(const Fixed &fixed) {
    Fixed fix;

    fix.value = value - fixed.value;
    return fix;
}

Fixed Fixed::operator*(const Fixed &fixed) {
    Fixed fix;

    fix.value = (value * fixed.value) / (1 << fraction);
    return fix;
}

Fixed Fixed::operator/(const Fixed &fixed) {
    Fixed fix;

    fix.value = (value / fixed.value) * (1 << fraction);
    return fix;
}

Fixed Fixed::operator++(void) {
    ++this->value;
    return *this;
}

Fixed Fixed::operator++(int) {
    Fixed tmp = *this;

    this->value++;
    return tmp;
}

Fixed Fixed::operator--(void) {
    --this->value;
    return *this;
}
Fixed Fixed::operator--(int) {
    Fixed tmp = *this;

    this->value--;
    return tmp;
}

Fixed &Fixed::min(Fixed &fixed1, Fixed &fixed2) {
    if (fixed1.toFloat() < fixed2.toFloat()) {
        return fixed1;
    }
    return fixed2;
}

const Fixed &Fixed::min(const Fixed &fixed1, const Fixed &fixed2) {
    if (fixed1.toFloat() < fixed2.toFloat()) {
        return fixed1;
    }
    return fixed2;
}

Fixed &Fixed::max(Fixed &fixed1, Fixed &fixed2) {
    if (fixed1.toFloat() > fixed2.toFloat()) {
        return fixed1;
    }
    return fixed2;
}

const Fixed &Fixed::max(const Fixed &fixed1, const Fixed &fixed2) {
    if (fixed1.toFloat() > fixed2.toFloat()) {
        return fixed1;
    }
    return fixed2;
}

int Fixed::toInt(void) const { return value / static_cast<int>(1 << fraction); }

float Fixed::toFloat(void) const {
    return static_cast<float>(value) / static_cast<float>(1 << fraction);
}

int Fixed::getRawBits(void) const { return value; }

void Fixed::setRawBits(int const raw) { value = raw; }

Fixed::~Fixed() {}

std::ostream &operator<<(std::ostream &os, const Fixed &fixed) {
    os << fixed.toFloat();
    return os;
}
