#include "../include/Span.hpp"
#include <chrono>

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
    : data(std::move(rhs.data)), size(rhs.size), min(rhs.min), max(rhs.max) {}

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
    auto start = std::chrono::high_resolution_clock::now();
    if (data.size() >= size) {
        throw std::out_of_range("Cannot add more numbers, container is full");
    }

    auto insert_pos = std::lower_bound(data.begin(), data.end(), x);
    data.insert(insert_pos, x);

    if (data.size() >= 2) {
        min = UINT_MAX;
        auto current = data.begin();
        auto next = std::next(current);

        while (next != data.end()) {
            long long diff = static_cast<long long>(*next) -
                             static_cast<long long>(*current);
            auto current_span = static_cast<unsigned int>(std::abs(diff));
            min = std::min(min, current_span);

            current = next;
            ++next;
        }

        max = static_cast<unsigned int>(
            std::abs(static_cast<long long>(data.back()) -
                     static_cast<long long>(data.front())));
    }
    // End timing
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate duration in microseconds
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // Print the duration
    std::cout << "addNumber took " << duration.count() << " microseconds\n";
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

void Span::printer() {
    for (int nbr : data) {
        std::cerr << nbr << '\n';
    }

    std::cerr << min << '\n' << max << '\n';
}

Span::~Span() {}

std::vector<int> randomVector(unsigned int N) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(std::numeric_limits<int>::min(),
                                        std::numeric_limits<int>::max());

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> tmp;
    tmp.reserve(N);

    while (tmp.size() < N) {
        tmp.push_back(dis(gen));
    }

        // End timing
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate duration in microseconds
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // Print the duration
    std::cout << "randomVector took " << duration.count() << " microseconds\n";
    return tmp;
}
