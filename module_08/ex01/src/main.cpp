#include "../tester/include/tester.hpp"




/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 18:44:22 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/11/02 02:12:39 by lvan-gef      ########   odam.nl         */
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
    if (argc != 2) {
        std::cerr << "Expect 1 argument got: " << argc << std::endl;
        return 1;
    }

    int amount = std::atoi(argv[1]);

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> rv = randomVector(amount);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Create random data<" << amount << "> duration: " << duration.count() << " milliseconds" << '\n';

    start = std::chrono::high_resolution_clock::now();
    Span x = Span(rv.begin(), rv.end());
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Add           data<" << amount << "> duration: " << duration.count() << " milliseconds" << '\n';

    start = std::chrono::high_resolution_clock::now();
    x.printer();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Print         data<" << amount << "> duration: " << duration.count() << " milliseconds" << '\n';

    start = std::chrono::high_resolution_clock::now();
    unsigned int shortes = x.shortestSpan();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Shortes       span<" << amount << "> duration: " << duration.count() << " milliseconds" << '\n';

    start = std::chrono::high_resolution_clock::now();
    unsigned int longest = x.longestSpan();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Longest       span<" << amount << "> duration: " << duration.count() << " milliseconds" << '\n';

    std::cout << shortes << std::endl;
    std::cout << longest << std::endl;

    subject_test(false);
    (void)argc;
    (void)argv;
}
