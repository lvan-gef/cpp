#include "PmergeDeque.hpp"

#include <algorithm>
#include <chrono>
#include <climits>
#include <cstdlib>
#include <deque>
#include <iostream>

void PmergeDeque::sort(int size, char **args) {
    std::size_t max_seq = 7;
    std::cout << "Before: ";
    std::size_t index = 1;
    for (; index < max_seq + 1 && index < (std::size_t)size; ++index) {
        std::cout << args[index] << " ";
    }

    if (index < (std::size_t)size) {
        std::cout << "[...]";
    }
    std::cout << '\n';

    auto start = std::chrono::high_resolution_clock::now();

    std::deque<int> deq;

    if (_parseInputDeque(size, args, deq) != true) {
        return;
    }

    deq = _fordJohnsonSort(deq);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    _printSeq(deq, max_seq);
    std::cout << "Time to process a range of " << size
              << " elements with std::deq: " << duration.count() << " us"
              << '\n'
              << '\n';
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

    std::deque<int> small, large;
    int extra = -1;

    for (size_t i = 0; i + 1 < arr.size(); i += 2) {
        int a = arr[i];
        int b = arr[i + 1];
        if (a > b) {
            std::swap(a, b);
        }

        small.push_back(a);
        large.push_back(b);
    }

    if (arr.size() % 2 == 1) {
        extra = arr.back();
    }

    small = _fordJohnsonSort(small);

    std::deque<size_t> jacobsthal = _generateJacob(large.size());

    std::deque<int> result = small;
    if (!large.empty()) {
        for (int i : large) {
            auto it = std::upper_bound(result.begin(), result.end(), i);
            long int actualPos = it - result.begin();
            result.insert(result.begin() + actualPos, i);
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
                                   std::deque<int> &deq) {
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

void PmergeDeque::_printSeq(const std::deque<int> &deq, std::size_t max_print) {
    auto start = deq.begin();
    auto end = deq.end();
    std::size_t index = 0;

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
