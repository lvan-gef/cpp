#include "../include/Span.hpp"

Span::Span(unsigned int N) : size(N) {};

Span::Span(const Span &rhs)
    : data(rhs.data), size(rhs.size) {}

Span &Span::operator=(const Span &rhs) {
    if (this != &rhs) {
        data = rhs.data;
        size = rhs.size;
    }

    return *this;
}

Span::Span(Span &&rhs) noexcept
    : data(std::move(rhs.data)), size(rhs.size) {}

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
        long long diff =
            static_cast<long long>(*next) - static_cast<long long>(*it);
        auto current_span = static_cast<unsigned int>(std::abs(diff));
        min_span = std::min(min_span, current_span);
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

    return static_cast<unsigned int>(std::abs(last - first));
}

void Span::printer() {
    for (int nbr : data) {
        std::cerr << nbr << '\n';
    }
}

Span::~Span() {}
