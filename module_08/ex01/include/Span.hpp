#ifndef SPAN_HPP
#define SPAN_HPP

#include <climits>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

class Span {
  public:
    explicit Span(unsigned int N);

    Span(const Span &rhs);
    Span &operator=(const Span &rhs);

    Span(Span &&rhs) noexcept;
    Span &operator=(Span &&rhs) noexcept;

    void addNumber(int x);
    unsigned int shortestSpan() const;
    unsigned int longestSpan() const;
    void printer();

    // add member to fill it with numbers in a iter form
    void randomFill();

    ~Span();

  private:
    std::vector<int> data;
    unsigned int size;
    unsigned int min;
    unsigned int max;
};

#endif // !SPAN_HPP
