/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Point.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 23:13:34 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/02/04 03:53:08 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Point.hpp"

Point::Point() : x(Fixed(0)), y(Fixed(0)) {}
Point::Point(const float px, const float py) : x(Fixed(px)), y(Fixed(py)) {}

Point::Point(const Point &point) : x(point.x), y(point.y) {}
Point &Point::operator=(const Point &point) {
  (void)point;
  return *this;
}

float Point::getFloatX(void) const { return x.toFloat(); }
float Point::getFloatY(void) const { return y.toFloat(); }

Point::~Point() {}
