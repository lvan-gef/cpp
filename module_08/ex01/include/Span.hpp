#ifndef SPAN_HPP
#define SPAN_HPP

#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

class Span {
  public:
    explicit Span(unsigned int N);

    template <typename Iterator>
    explicit Span(Iterator begin, Iterator end)
        : size(std::distance(begin, end)), min(0), max(0) {

        data.reserve(size);
        for (Iterator it = begin; it != end; ++it) {
            addNumber(*it);
        }
    }

    Span(const Span &rhs);
    Span &operator=(const Span &rhs);

    Span(Span &&rhs) noexcept;
    Span &operator=(Span &&rhs) noexcept;

    void addNumber(int x);
    unsigned int shortestSpan() const;
    unsigned int longestSpan() const;
    void printer();

    ~Span();

  private:
    std::vector<int> data;
    unsigned int size;
    unsigned int min;
    unsigned int max;
};

std::vector<int> randomVector(unsigned int N);
#endif // !SPAN_HPP
