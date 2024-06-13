/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Point.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 23:13:20 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/02/03 23:48:08 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef Point_H
#define Point_H

#include "./Fixed.hpp"

class Point {
 public:
  Point();
  Point(const float x, const float y);

  Point(const Point &point);
  Point &operator=(const Point &point);

  float getFloatX(void) const;
  float getFloatY(void) const;
  ~Point();

 private:
  const Fixed x;
  const Fixed y;
};

#endif
