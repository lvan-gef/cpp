/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 23:12:46 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/02/03 23:24:02 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <iostream>
#include <sstream>

#include "../include/Fixed.hpp"

int main() {
  std::cout << "Test default constructor\n";
  Fixed a;
  assert(a.getRawBits() == 0);

  std::cout << "\nTest int constructor\n";
  Fixed b(5);
  assert(b.toInt() == 5);

  std::cout << "\nTest float constructor\n";
  Fixed c(5.05f);
  assert(c.toFloat() >= 5.05f &&
         c.toFloat() < 5.06f);  // Depending on your precision

  std::cout << "\nTest Copy constructor\n";
  Fixed d(b);
  assert(d.toInt() == 5);

  std::cout << "\nTest Copy Assignment operator\n";
  Fixed e;
  e = d;
  assert(e.toInt() == 5);

  std::cout << "\nTest Copy Assignment operator to it self\n";
  e = e;
  assert(e.toInt() == 5);

  std::cout << "\nTest setRawBits and getRawBits\n";
  Fixed f;
  f.setRawBits(256);
  assert(f.getRawBits() == 256);

  std::cout << "\nTest toFloat\n";
  Fixed g;
  g.setRawBits(256);
  assert(g.toFloat() == 1.0f);

  std::cout << "\nTest toInt\n";
  Fixed i(5.75f);
  assert(i.toInt() == 5);

  std::cout << "\nTest Output overloader\n";
  Fixed k(5.5f);
  std::ostringstream oss;
  oss << k;
  assert(oss.str() == "5.5");

  std::cout << "\nAll tests passed successfully.\n\n";

  return 0;
}
