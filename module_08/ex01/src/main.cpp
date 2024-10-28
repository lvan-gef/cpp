#include "../include/Span.hpp"
#include <cassert>
#include <stdexcept>

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

static void subject_test() {
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
    sp.printer();
    assert(sp.shortestSpan() == 2 && "Expect that shortestSpan is 2");
    assert(sp.longestSpan() == 14 && "Expect that longestSpan is 14");

    // sp.addNumber(12);
    // assert(sp.shortestSpan() == 1 && "Expect that shortestSpan is 1");
    // assert(sp.longestSpan() == 14 && "Expect that longestSpan is 14");
}

int main(int argc, char **argv) {
    subject_test();

    if (argc != 2) {
        std::cerr << "Expect 1 argument got: " << argc << '\n';
        return 1;
    }

    (void)argv;
    // int amount = std::atoi(argv[1]);
    // Span x = Span(amount);
    //
    // x.randomFill();
    // x.printer();
    //
    // int shortes = x.shortestSpan();
    // int longest = x.longestSpan();
    //
    // std::cout << shortes << '\n';
    // std::cout << longest << '\n';
}
