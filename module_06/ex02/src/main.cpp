/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 19:54:24 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/15 19:13:40 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/A.hpp"
#include "../include/B.hpp"
#include "../include/C.hpp"
#include "../include/Tester.hpp"

static Base *generator() {
    uint64_t seed = std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::system_clock::now().time_since_epoch())
                        .count();
    srand(seed);
    int random = rand() % 3;

    switch (random % 3) {
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
        std::cout << "A" << std::endl;
    } else if (dynamic_cast<B *>(p) != nullptr) {
        std::cout << "B" << std::endl;
    } else if (dynamic_cast<C *>(p) != nullptr) {
        std::cout << "C" << std::endl;
    } else {
        std::cerr << "Unknown type" << std::endl;
    }
}

static void identify(Base &p) {
    try {
        (void)dynamic_cast<A &>(p);
        std::cout << "A" << std::endl;
    } catch (std::bad_cast const &) {
        try {
            (void)dynamic_cast<B &>(p);
            std::cout << "B" << std::endl;
        } catch (std::bad_cast const &) {
            try {
                (void)dynamic_cast<C &>(p);
                std::cout << "C" << std::endl;
            } catch (std::bad_cast const &e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }
}

int main() {
    testGenerator(generator);
    std::cout << "generator() test passed!" << '\n' << '\n';

    testIdentifyPointer(static_cast<void (*)(Base *)>(identify));
    std::cout << "identify(Base*) test passed!" << '\n' << '\n';

    testIdentifyReference([](Base &p) { identify(p); });
    std::cout << "identify(Base&) test passed!" << '\n' << '\n';

    testEdgeCases(static_cast<void (*)(Base *)>(identify),
                  [](Base &p) { identify(p); });
    std::cout << "Edge cases test passed!" << '\n' << '\n';

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
