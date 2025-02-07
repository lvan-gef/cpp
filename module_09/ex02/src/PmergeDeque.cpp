#include <algorithm>
#include <chrono>
#include <climits>
#include <cstdlib>
#include <deque>
#include <iostream>

#include "PmergeDeque.hpp"

PmergeDeque::PmergeDeque() {
}

PmergeDeque::PmergeDeque(const PmergeDeque &rhs) {
    (void)rhs;
};

PmergeDeque &PmergeDeque::operator=(const PmergeDeque &rhs) {
    if (this != &rhs) {
    }

    return *this;
}

PmergeDeque::PmergeDeque(PmergeDeque &&rhs) noexcept {
    (void)rhs;
}

PmergeDeque &PmergeDeque::operator=(PmergeDeque &&rhs) noexcept {
    if (this != &rhs) {
    }

    return *this;
}

PmergeDeque::~PmergeDeque() {
}

std::deque<int> PmergeDeque::sort(int size, char **args) const {
    if (size < 2) {
        std::cerr << "Expect at least 1 argument got: 0" << '\n';
        errno = EINVAL;
        return {};
    }

    int max_seq = 10;
    std::cout << "Before: ";
    int index = 1;
    for (; index < max_seq + 1 && index < size; ++index) {
        std::cout << args[index] << " ";
    }

    if (index < size) {
        std::cout << "[...]";
    }
    std::cout << '\n';

    auto start = std::chrono::high_resolution_clock::now();

    std::deque<int> deq;

    if (_parseInputDeque(size, args, deq) != true) {
        errno = EINVAL;
        return deq;
    }

    deq = _fordJohnsonSort(deq);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    printSeq(deq, max_seq);
    std::cout << "Time to process a range of " << size - 1
              << " elements with std::deq: " << duration.count() << " us"
              << '\n'
              << '\n';

    return deq;
}

void PmergeDeque::printSeq(const std::deque<int> &deq, int max_print) const {
    auto start = deq.begin();
    auto end = deq.end();
    int index = 0;

    std::cout << "After : ";
    while (index < max_print && start != end) {
        std::cout << *start << " ";
        start++;
        index++;
    }

    if (start != end) {
        std::cout << "[...]";
    }

    std::cout << '\n';
}

std::deque<std::size_t> PmergeDeque::_generateJacob(std::size_t n) const {
    std::deque<size_t> jacobsthal = {0, 1};

    while (jacobsthal.back() < n) {
        jacobsthal.push_back(jacobsthal[jacobsthal.size() - 1] +
                             2 * jacobsthal[jacobsthal.size() - 2]);
    }

    return jacobsthal;
}

std::deque<int>
PmergeDeque::_fordJohnsonSort(const std::deque<int> &arr) const {
    if (arr.size() <= 1) {
        return arr;
    }

    std::deque<int> smallSeq, largeSeq;
    int extra = -1;

    for (size_t index = 0; index + 1 < arr.size(); index += 2) {
        int a = arr[index];
        int b = arr[index + 1];
        if (a > b) {
            std::swap(a, b);
        }

        smallSeq.push_back(a);
        largeSeq.push_back(b);
    }

    if (arr.size() % 2 == 1) {
        extra = arr.back();
    }

    smallSeq = _fordJohnsonSort(smallSeq);

    std::deque<size_t> jacobsthal = _generateJacob(largeSeq.size());

    std::deque<int> result = smallSeq;
    if (!largeSeq.empty()) {
        for (int index : largeSeq) {
            auto it = std::upper_bound(result.begin(), result.end(), index);
            long int actualPos = it - result.begin();
            result.insert(result.begin() + actualPos, index);
        }
    }

    if (extra != -1) {
        auto it = std::upper_bound(result.begin(), result.end(), extra);
        long int pos = it - result.begin();
        result.insert(result.begin() + pos, extra);
    }

    return result;
}

bool PmergeDeque::_parseInputDeque(int size, char **args,
                                   std::deque<int> &deq) const {
    for (int index = 1; index < size; ++index) {
        int value = _toInt(args[index]);
        if (errno != 0) {
            return false;
        }

        deq.emplace_back(value);
    }

    return true;
}

int PmergeDeque::_toInt(char *str) const {
    char *endptr = nullptr;
    long int value = strtol(str, &endptr, 10);

    if (endptr == str) {
        std::cerr << "No digits found" << '\n';
        errno = EINVAL;
        return 0;
    } else if (*endptr != '\0') {
        std::cerr << "Invalid arr" << '\n';
        errno = EINVAL;
        return 0;
    } else {
        if (value > INT_MAX) {
            std::cerr << "Interger overflow" << '\n';
            errno = ERANGE;
            return 0;
        } else if (value < INT_MIN) {
            std::cerr << "Interger underflow" << '\n';
            errno = ERANGE;
            return 0;
        }
    }

    return static_cast<int>(value);
}
