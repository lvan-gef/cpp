#include "../include/Span.hpp"

Span::Span(unsigned int N) : size(N), min(0), max(0) { data.reserve(N); }

Span::Span(const Span &rhs) : data(rhs.data), size(rhs.size) {}

Span &Span::operator=(const Span &rhs) {
    if (this != &rhs) {
    }

    return *this;
}

Span::Span(Span &&rhs) noexcept { (void)rhs; }

Span &Span::operator=(Span &&rhs) noexcept {
    if (this != &rhs) {
    }

    return *this;
}

void Span::addNumber(int x) {
    if (data.size() == data.capacity()) {
        throw std::out_of_range("Span is full\n");
    }

    if (data.size() == 0) {
        data.push_back(x);
        return;
    }

    std::cout << data.size() << '\n';
    unsigned int index = 0;
    for (index = 0; index < data.size(); index++) {
        if (data.size() > 0 && x < data[index]) {
            if (index == 0) {
                std::cout << "x: " << x << " is kleiner dan elm 0: " << data[index] << '\n';
                min = data[index] - x;
                max = data[index] - x;
                data.insert(data.begin(), x);
                return;
            }

            std::cout << "x: " << x << " is kleiner dan elm " << index << ": " << data[index] << '\n';
            if ((unsigned int)data[index] - x < min) {
                min = data[index] - x;
            }
            data.insert(data.begin() + index, x);

            // update min
            // min = data[index] - x;
            // min = x - data[index];
            return;
        }
    }

    std::cout << "x: " << x << " is groter dan elm " << index << ": " << data[index - 1] << '\n';
    max = x - data[0];
    data.push_back(x);
    return;

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

    std::cerr << "min: " << min << '\n' << "max: " << max << '\n';
}

Span::~Span() {}
