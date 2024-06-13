/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Fixed.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 23:12:34 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 22:22:39 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef Fixed_h
#define Fixed_h

#include <cmath>
#include <iostream>

class Fixed {
  public:
    Fixed();
    explicit Fixed(const int &number);
    explicit Fixed(const float &number);
    Fixed(const Fixed &fixed);
    Fixed &operator=(const Fixed &fixed);

    int toInt(void) const;
    float toFloat(void) const;
    int getRawBits(void) const;
    void setRawBits(int const raw);

    ~Fixed();

  private:
    int value;
    static const int fraction = 8;
};

std::ostream &operator<<(std::ostream &os, const Fixed &fixed);
#endif
