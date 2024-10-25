#include "../include/Span.hpp"
#include <stdexcept>

Span::Span(unsigned int N) : data(N), size(N) {}

Span::Span(const Span &rhs) : data(rhs.data), size(rhs.size) {}

Span &Span::operator=(const Span &rhs) {
    std::cout << "Copy assigment constructor for Span is called" << '\n';
    if (this != &rhs) {
    }

    return *this;
}

Span::Span(Span &&rhs) noexcept {
    (void)rhs;
    std::cout << "Default move constructor for Span is called" << '\n';
}

Span &Span::operator=(Span &&rhs) noexcept {
    std::cout << "Move assigment constructor for Span is called" << '\n';
    if (this != &rhs) {
    }

    return *this;
}

void Span::addNumber(int x) {
    if (data.size() < size) {
        data.push_back(x);
        return;
    }

    throw std::out_of_range("Span is full\n");
}

int Span::shortestSpan() {
    if (data.size() < 2) {
        throw std::out_of_range("Not enough elements in Span");
    }

    int minDist = INT_MAX;
    for (size_t i = 0; i < size; i++) {
        for (size_t j = i + 1; j < size; j++) {
            minDist = std::min(minDist, abs(data[i] - data[j]));
        }
    }

    return minDist;
}

int Span::longestSpan() {
    if (data.size() < 2) {
        throw std::out_of_range("Not enough elements in Span");
    }

    return -1;
}

Span::~Span() {}
