/* ************************************************************************** */
/*                                                                            */
/*   main.cpp                                           :+:    :+:            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Updated: 2024/11/02 18:39:28 by lvan-gef      ########   odam.nl         */
/*   Updated: 2024/11/02 18:42:43 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Span.hpp"

static void check_fail(Span sp) {
    try {
        sp.shortestSpan();
    } catch (std::out_of_range &e) {
        static_assert(true, "");
    } catch (...) {
        assert(false && "Unknow error was throw to me in shortestSpan...\n");
    }
    try {
        sp.longestSpan();
    } catch (std::out_of_range &e) {
        static_assert(true, "");
    } catch (...) {
        assert(false && "Unknow error was throw to me in longestSpan...\n");
    }
}

static void subject_test(bool isPrint) {
    if (isPrint == true) {
    std::cout << "Start subject test" << '\n';
    }

    Span sp = Span(6);
    check_fail(sp);

    sp.addNumber(6);
    check_fail(sp);

    sp.addNumber(3);
    check_fail(sp);

    assert(sp.shortestSpan() == 3 && "Expect that shortestSpan is 3");
    assert(sp.longestSpan() == 3 && "Expect that longestSpan is 3");

    sp.addNumber(17);
    assert(sp.shortestSpan() == 3 && "Expect that shortestSpan is 3");
    assert(sp.longestSpan() == 14 && "Expect that longestSpan is 14");

    sp.addNumber(9);
    assert(sp.shortestSpan() == 3 && "Expect that shortestSpan is 3");
    assert(sp.longestSpan() == 14 && "Expect that longestSpan is 14");

    sp.addNumber(11);
    assert(sp.shortestSpan() == 2 && "Expect that shortestSpan is 2");
    assert(sp.longestSpan() == 14 && "Expect that longestSpan is 14");

    sp.addNumber(12);
    assert(sp.shortestSpan() == 1 && "Expect that shortestSpan is 1");
    assert(sp.longestSpan() == 14 && "Expect that longestSpan is 14");

    if (isPrint == true) {
    std::cout << "Pass subject test" << '\n';
    }
}

int main(int argc, char **argv) {
    subject_test(true);

    (void)argc;
    (void)argv;
}
