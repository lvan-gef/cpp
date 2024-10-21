/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 19:54:24 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/22 00:42:36 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/A.hpp"
#include "../include/B.hpp"
#include "../include/C.hpp"
#include "../include/Tester.hpp"

static Base *generate() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    std::uniform_int_distribution<int> distribution(0, 2);
    int random_number = distribution(generator);
    switch (random_number) {
        case 0:
            return new A();
        case 1:
            return new B();
        case 2:
            return new C();
        default:
            return nullptr;
    }
}

static void identify(Base *p) {
    if (dynamic_cast<A *>(p) != nullptr) {
        std::cout << "A" << '\n';
    } else if (dynamic_cast<B *>(p) != nullptr) {
        std::cout << "B" << '\n';
    } else if (dynamic_cast<C *>(p) != nullptr) {
        std::cout << "C" << '\n';
    } else {
        std::cerr << "Unknown type" << '\n';
    }
}

static void identify(Base &p) {
    try {
        (void)dynamic_cast<A &>(p);
        std::cout << "A" << '\n';
    } catch (std::bad_cast const &) {
        try {
            (void)dynamic_cast<B &>(p);
            std::cout << "B" << '\n';
        } catch (std::bad_cast const &) {
            try {
                (void)dynamic_cast<C &>(p);
                std::cout << "C" << '\n';
            } catch (std::bad_cast const &e) {
                std::cerr << e.what() << '\n';
            }
        }
    }
}

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
