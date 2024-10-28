#include "../include/Span.hpp"

Span::Span(unsigned int N) : size(N), min(0), max(0) { data.reserve(N); }


Span::Span(const Span &rhs)
    : data(rhs.data), size(rhs.size), min(rhs.min), max(rhs.max) {}

Span &Span::operator=(const Span &rhs) {
    if (this != &rhs) {
        data = rhs.data;
        size = rhs.size;
        min = rhs.min;
        max = rhs.max;
    }

    return *this;
}

Span::Span(Span &&rhs) noexcept
    : data(std::move(rhs.data)), size(rhs.size),
      min(rhs.min), max(rhs.max) {}

Span &Span::operator=(Span &&rhs) noexcept {
    if (this != &rhs) {
        data = std::move(rhs.data);
        size = rhs.size;
        min = rhs.min;
        max = rhs.max;
    }

    return *this;
}

void Span::addNumber(int x) {
    if (data.size() >= size) {
        throw std::out_of_range("Cannot add more numbers, container is full");
    }

    data.push_back(x);
    std::sort(data.begin(), data.end(), std::less<int>());

    if (data.size() >= 2) {
        min = UINT_MAX;
        for (size_t i = 1; i < data.size(); i++) {
            long long diff = static_cast<long long>(data[i]) -
                             static_cast<long long>(data[i - 1]);
            auto current_span = static_cast<unsigned int>(std::abs(diff));
            min = std::min(min, current_span);
        }

        auto largest = static_cast<long long>(data.back());
        auto smallest = static_cast<long long>(data.front());
        max = static_cast<unsigned int>(std::abs(largest - smallest));
    }
}

unsigned int Span::shortestSpan() const {
    if (data.size() < 2) {
        throw std::out_of_range("Not enough elements in Span");
    }

    return min;
}

unsigned int Span::longestSpan() const {
    if (data.size() < 2) {
        throw std::out_of_range("Not enough elements in Span");
    }

    return max;
}

void Span::randomFill() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(std::numeric_limits<int>::min(),
                                        std::numeric_limits<int>::max());

    while (data.size() < size) {
        addNumber(dis(gen));
    }
}

void Span::printer() {
    for (int nbr : data) {
        std::cerr << nbr << '\n';
    }

    std::cerr << min << '\n' << max << '\n';
}

Span::~Span() {}
