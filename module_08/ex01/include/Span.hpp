#ifndef SPAN_HPP
#define SPAN_HPP

#include <cassert>
#include <climits>
#include <iostream>
#include <random>
#include <set>

class Span {
  public:
    explicit Span(unsigned int N);

    template <typename Iterator>
    explicit Span(Iterator begin, Iterator end)
        : size(std::distance(begin, end)) {

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
    std::multiset<int> data;
    unsigned int size;
};

std::vector<int> randomVector(unsigned int N);
#endif // !SPAN_HPP
