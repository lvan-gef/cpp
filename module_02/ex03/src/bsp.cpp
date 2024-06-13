/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bsp.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 23:13:34 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 22:22:39 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Point.hpp"

static float ft_abs(float number) {
    if (number < 0) {
        return -number;
    }

    return number;
}

static float areaTriangle(Point const a, Point const b, Point const c) {
    return ft_abs(a.getFloatX() * (b.getFloatY() - c.getFloatY()) +
                  b.getFloatX() * (c.getFloatY() - a.getFloatY()) +
                  c.getFloatX() * (a.getFloatY() - b.getFloatY())) /
           2.0f;
}

static float triangleSign(Point const a, Point const b, Point const c) {
    return (a.getFloatX() - c.getFloatX()) * (b.getFloatY() - c.getFloatY()) -
           (b.getFloatX() - c.getFloatX()) * (a.getFloatY() - c.getFloatY());
}

bool bsp(Point const a, Point const b, Point const c, Point const point) {
    if (areaTriangle(a, b, c) <= 0) {
        return false;
    }

    float a1 = triangleSign(point, a, b);
    float b1 = triangleSign(point, b, c);
    float c1 = triangleSign(point, c, a);

    if (a1 == 0 || b1 == 0 || c1 == 0) {
        return false;
    }

    bool has_negative = (a1 < 0) || (b1 < 0) || (c1 < 0);
    bool has_posative = (a1 > 0) || (b1 > 0) || (c1 > 0);

    return !(has_negative && has_posative);
}
