#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>
#include <stdexcept>

template <typename T, typename Func>
void iter(T *arr, size_t size, Func func) {
    if (arr == nullptr) {
        throw std::invalid_argument("T1 can not be a nullptr\n");
    }

    if (size == 0) {
        throw std::invalid_argument("T2 must be more then 0\n");
    }

    try {
        for (size_t i = 0; i < size; i++) {
            func(arr[i]);
        }
    } catch (std::exception &e) {
        std::cerr << e.what();
        throw;
    }
}

#endif // !ITER_HPP
