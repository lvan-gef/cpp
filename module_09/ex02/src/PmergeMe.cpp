#include <algorithm>
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>
#include <chrono>

#include "../include/PmergeMe.hpp"

void PmergeMe::run_list(int size, char **args) {
    auto start = std::chrono::high_resolution_clock::now();

    std::list<int> list((size_t)size);

    if (_parse_input_list(size, args, list) != true) {
        return;
    }

    if (list.size() <= 1) {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Time to process a range of " << size
                  << " elements with std::list: " << duration.count() << " us"
                  << '\n';
        return;
    }

    if (list.size() == 2) {
        if (*list.begin() > *list.end()) {
            std::list<int>::iterator it = list.begin();
            std::list<int>::iterator next_it = std::next(it);
            std::iter_swap(it, next_it);
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Time to process a range of " << size
                  << " elements with std::list: " << duration.count() << " us"
                  << '\n';
        return;
    }

    ford_johnson_sort<std::list<int>, int>(list);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time to process a range of " << size
              << " elements with std::list: " << duration.count() << " us"
              << '\n';
}

void PmergeMe::run_vector(int size, char **args) {
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> vector;
    vector.reserve((size_t)size);

    if (_parse_input_vector(size, args, vector) != true) {
        return;
    }

    if (vector.size() <= 1) {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Time to process a range of " << size
                  << " elements with std::vector: " << duration.count() << " us"
                  << '\n';
        return;
    }

    ford_johnson_sort<std::vector<int>, int>(vector);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time to process a range of " << size
              << " elements with std::vector: " << duration.count() << " us"
              << '\n';
}

// private
bool PmergeMe::_parse_input_list(int size, char **args, std::list<int> &lis) {
    std::list<int>::iterator it = lis.begin();

    for (int index = 1; index < size; index++, ++it) {
        int value = _toInt(args[index]);
        if (errno != 0) {
            return false;
        }
        *it = value;
    }

    return true;
}

bool PmergeMe::_parse_input_vector(int size, char **args,
                                   std::vector<int> &vec) {
    for (int index = 1; index < size; index++) {
        int value = _toInt(args[index]);
        if (errno != 0) {
            return false;
        }

        vec.emplace_back(value);
    }

    return true;
}

int PmergeMe::_toInt(char *str) {
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
