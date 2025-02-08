#include <algorithm>
#include <chrono>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "../include/PmergeVector.hpp"

PmergeVector::PmergeVector() {
}

PmergeVector::PmergeVector(const PmergeVector &rhs) {
    (void)rhs;
}

PmergeVector &PmergeVector::operator=(const PmergeVector &rhs) {
    if (this != &rhs) {
    }

    return *this;
}

PmergeVector::PmergeVector(PmergeVector &&rhs) noexcept {
    (void)rhs;
}

PmergeVector &PmergeVector::operator=(PmergeVector &&rhs) noexcept {
    if (this != &rhs) {
    }

    return *this;
}

PmergeVector::~PmergeVector() {
}

std::vector<int> PmergeVector::sort(int size, char **args) const {
    if (size < 2) {
        std::cerr << "Error: Expect at least 1 argument got: 0" << '\n';
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

    std::vector<int> vec;
    vec.reserve((size_t)size);

    if (_parseInputVector(size, args, vec) != true) {
        errno = EINVAL;
        return {};
    }

    vec = _fordJohnsonSort(vec);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    printSeq(vec, max_seq);
    std::cout << "Time to process a range of " << size - 1
              << " elements with std::vector: " << duration.count() << " us"
              << '\n'
              << '\n';

    return vec;
}

void PmergeVector::printSeq(const std::vector<int> &vec, int max_print) const {
    auto start = vec.begin();
    auto end = vec.end();
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

std::vector<std::size_t> PmergeVector::_generateJacob(std::size_t n) const {
    std::vector<size_t> jacobsthal = {0, 1};
    jacobsthal.reserve(n);

    while (jacobsthal.back() < n) {
        jacobsthal.emplace_back(jacobsthal[jacobsthal.size() - 1] +
                                2 * jacobsthal[jacobsthal.size() - 2]);
    }

    return jacobsthal;
}

std::vector<int>
PmergeVector::_fordJohnsonSort(const std::vector<int> &arr) const {
    if (arr.size() <= 1) {
        return arr;
    }

    std::vector<int> smallSeq, largeSeq;
    int extra = -1;

    for (size_t index = 0; index + 1 < arr.size(); index += 2) {
        int a = arr[index];
        int b = arr[index + 1];
        if (a > b) {
            std::swap(a, b);
        }

        smallSeq.emplace_back(a);
        largeSeq.emplace_back(b);
    }

    if (arr.size() % 2 == 1) {
        extra = arr.back();
    }

    smallSeq = _fordJohnsonSort(smallSeq);

    std::vector<size_t> jacobsthal = _generateJacob(largeSeq.size());

    std::vector<int> result = smallSeq;
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

bool PmergeVector::_parseInputVector(int size, char **args,
                                     std::vector<int> &vec) const {
    for (int index = 1; index < size; ++index) {
        int value = _toInt(args[index]);
        if (errno != 0) {
            return false;
        }

        vec.emplace_back(value);
    }

    return true;
}

int PmergeVector::_toInt(char *str) const {
    char *endptr = nullptr;
    long int value = strtol(str, &endptr, 10);

    if (endptr == str) {
        std::cerr << "Error: A non digit char found" << '\n';
        errno = EINVAL;
        return 0;
    } else if (*endptr != '\0') {
        std::cerr << "Error: Invalid argument" << '\n';
        errno = EINVAL;
        return 0;
    } else {
        if (value > INT_MAX) {
            std::cerr << "Error: Interger overflow" << '\n';
            errno = ERANGE;
            return 0;
        } else if (value < 0) {
            std::cerr << "Error: invalid interger" << '\n';
            errno = ERANGE;
            return 0;
        }
    }

    return static_cast<int>(value);
}
