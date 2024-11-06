/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Span.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 18:44:22 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/11/06 18:02:10 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Span.hpp"

Span::Span(unsigned int N) : size(N) {};

Span::Span(const Span &rhs) : data(rhs.data), size(rhs.size) {}

Span &Span::operator=(const Span &rhs) {
    if (this != &rhs) {
        data = rhs.data;
        size = rhs.size;
    }

    return *this;
}

Span::Span(Span &&rhs) noexcept : data(std::move(rhs.data)), size(rhs.size) {}

Span &Span::operator=(Span &&rhs) noexcept {
    if (this != &rhs) {
        data = std::move(rhs.data);
        size = rhs.size;
    }

    return *this;
}

void Span::addNumber(int x) {
    if (data.size() >= size) {
        throw std::out_of_range("Cannot add more numbers, container is full");
    }

    data.insert(x);
}

unsigned int Span::shortestSpan() const {
    if (data.size() < 2) {
        throw std::out_of_range("Not enough elements in Span");
    }

    unsigned int min_span = UINT_MAX;
    auto it = data.begin();
    auto next = std::next(it);

    while (next != data.end()) {
        min_span = std::min(min_span, static_cast<unsigned int>(*next - *it));
        it = next;
        ++next;
    }

    return min_span;
}

unsigned int Span::longestSpan() const {
    if (data.size() < 2) {
        throw std::out_of_range("Not enough elements in Span");
    }

    auto first = static_cast<long long>(*data.begin());
    auto last = static_cast<long long>(*data.rbegin());

    return static_cast<unsigned int>(last - first);
}

Span::~Span() {}
