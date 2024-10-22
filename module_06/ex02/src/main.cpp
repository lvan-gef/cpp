/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 19:54:24 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/22 17:45:29 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Tester.hpp"

int main() {
    testGenerator(generate);
    std::cout << "generator() test passed!" << '\n' << '\n';

    testIdentifyPointer(static_cast<void (*)(Base *)>(identify));
    std::cout << "identify(Base*) test passed!" << '\n' << '\n';

    testIdentifyReference([](Base &p) { identify(p); });
    std::cout << "identify(Base&) test passed!" << '\n' << '\n';

    testEdgeCases(static_cast<void (*)(Base *)>(identify),
                  [](Base &p) { identify(p); });
    std::cout << "Edge cases test passed!" << '\n' << '\n';

    std::cout << "All tests passed successfully!" << '\n';
    return 0;
}
