#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <vector>

class Span {
  public:
    explicit Span(unsigned int N);

    Span(const Span &rhs);
    Span &operator=(const Span &rhs);

    Span(Span &&rhs) noexcept;
    Span &operator=(Span &&rhs) noexcept;

    void addNumber(int x);
    int shortestSpan();
    int longestSpan();

    // add member to fill it with numbers in a iter form

    ~Span();

  private:
    std::vector<int> data;
    unsigned int size;
};

#endif // !SPAN_HPP
