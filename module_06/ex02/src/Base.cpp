/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Base.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 19:54:24 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/22 17:45:29 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Base.hpp"

Base::Base() { std::cout << "Default constructor for Base is called" << '\n'; }

Base::~Base() { std::cout << "Default destructor for Base is called" << '\n'; }

Base *generate() {
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

void identify(Base *p) {
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

void identify(Base &p) {
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
