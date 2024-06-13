/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/02 23:13:41 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 22:22:39 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>

#include "../include/Point.hpp"

bool bsp(Point const a, Point const b, Point const c, Point const point);

void runTest(float x1, float y1, float x2, float y2, float x3, float y3,
             float px, float py, bool state) {
    Point a(x1, y1), b(x2, y2), c(x3, y3), d(px, py);
    assert(bsp(a, b, c, d) == state);
}
int main(void) {
    std::cout << "Invalid traingle test\n";
    runTest(0, 0, 1, 1, 2, 2, 3, 3, false);
    runTest(0, 1, 1, 2, 2, 3, 3, 4, false);
    runTest(0, -1, 1, -2, 2, -3, 3, -4, false);

    std::cout << "Out of traingle test\n";
    runTest(0, 0, 5, 0, 2.5, 5, -1, -1, false);
    runTest(-1, 0, -5, 0, 2.5, 5, -1, -1, false);
    runTest(0, 0, 5, 0, 2.5, -5, 2.4, 2.5, false);
    runTest(10, 0, 20, 0, 15, 15, 5, 5, false);

    std::cout << "on edge of traingle\n";
    runTest(0, 0, 5, 0, 2.5, 5, 2.5, 0, false);
    runTest(30, 0, 50, 0, 40, 80, 40, 80, false);

    std::cout << "Inside of the traingle\n";
    runTest(0, 0, 5, 0, 2.5, 5, 2.4, 2.5, true);
    runTest(0, 0, 5, 0, 2.5, -5, 2.4, -2.5, true);
    runTest(-10, 0, -20, 0, -15, 15, -12, 5, true);

    return 0;
}
