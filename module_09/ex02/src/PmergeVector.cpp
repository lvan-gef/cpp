#include "PmergeVector.hpp"

#include <cstdlib>
#include <chrono>
#include <climits>
#include <iostream>
#include <vector>

PmergeVector::Pair::Pair(int a, int b) {
    if (a > b) {
        large = a;
        small = b;
    } else {
        large = b;
        small = a;
    }
}

void PmergeVector::sort(int size, char **args) {
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> arr;
    arr.reserve((size_t)size);

    if (_parse_input_vector(size, args, arr) != true) {
        return;
    }

    arr = ford_johnson_sort(arr);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time to process a range of " << size
              << " elements with std::vector: " << duration.count() << " us"
              << '\n';

    std::cout << *arr.begin() << '\n';
}

std::vector<std::size_t> PmergeVector::generate_jacob(std::size_t n) {
    std::vector<std::size_t> sequence;
    sequence.reserve(n);

    if (n == 0) {
        return sequence;
    }

    sequence.push_back(0);
    if (n == 1) {
        return sequence;
    }

    sequence.push_back(1);
    while (sequence.back() < n) {
        std::size_t next = sequence.back() + 2 * sequence[sequence.size() - 2];
        if (next > n) {
            break;
        }

        sequence.push_back(next);
    }

    return sequence;
}

void PmergeVector::insert(std::vector<int> &chain, int element,
                          std::size_t hint) {
    std::vector<int>::iterator start = chain.begin() + (long)hint;
    std::vector<int>::iterator pos =
        std::lower_bound(start, chain.end(), element);
    chain.insert(pos, element);
}

std::vector<int>
PmergeVector::ford_johnson_sort(const std::vector<int> &arr) const {
    if (arr.size() <= 1) {
        return arr;
    }

    std::vector<Pair> pairs;
    pairs.reserve(arr.size());

    std::size_t i = 0;
    for (; i + 1 < arr.size(); i += 2) {
        pairs.emplace_back(arr[i], arr[i + 1]);
    }

    int extra_element = 0;
    if (i < arr.size()) {
        extra_element = arr[i];
    }
    bool has_extra = i < arr.size();

    std::vector<int> small_elements;
    std::vector<int> large_elements;

    small_elements.reserve(pairs.size());
    large_elements.reserve(pairs.size());

    for (const auto &pair : pairs) {
        small_elements.push_back(pair.small);
        large_elements.push_back(pair.large);
    }

    if (small_elements.size() > 1) {
        small_elements = ford_johnson_sort(small_elements);
    }

    std::vector<int> result = small_elements;

    std::vector<std::size_t> jacobsthal = generate_jacob(pairs.size());

    if (!large_elements.empty()) {
        result.insert(result.begin() + 1, large_elements[0]);
    }

    for (std::size_t index = 1; index < jacobsthal.size(); ++index) {
        std::size_t current = jacobsthal[index];
        std::size_t next = (index + 1 < jacobsthal.size())
                               ? jacobsthal[index + 1]
                               : pairs.size();

        for (std::size_t sub_index = current;
             sub_index < next && sub_index < large_elements.size();
             ++sub_index) {
            insert(result, large_elements[sub_index], sub_index);
        }
    }

    if (has_extra) {
        auto pos =
            std::lower_bound(result.begin(), result.end(), extra_element);
        result.insert(pos, extra_element);
    }

    return result;
}

bool PmergeVector::_parse_input_vector(int size, char **args,
                                       std::vector<int> &vec) {
    for (int index = 1; index < size; ++index) {
        int value = _toInt(args[index]);
        if (errno != 0) {
            return false;
        }

        vec.emplace_back(value);
    }

    return true;
}

int PmergeVector::_toInt(char *str) {
    char *endptr = nullptr;
    long int value = strtol(str, &endptr, 10);

    if (endptr == str) {
        std::cerr << "No digits found" << '\n';
        errno = EINVAL;
        return 0;
    } else if (*endptr != '\0') {
        std::cerr << "Invalid input" << '\n';
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
