#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>
#include <stdexcept>

// template <typename T1, typename T2>
// void iter(T1 *arr, T2 size, void (*func)(T1 &)) {
//     static_assert(std::is_same<T2, std::size_t>::value, "T2 must be size_t");
//
//     if (arr == nullptr) {
//         throw std::invalid_argument("T1 can not be a nullptr\n");
//     }
//
//     if (size == 0) {
//         throw std::invalid_argument("T2 must be more then 0\n");
//     }
//
//     try {
//         for (size_t i = 0; i < size; i++) {
//             if (arr[i] == '\0') { // for c style array's
//                 return;
//             }
//             func(arr[i]);
//         }
//     } catch (std::exception &e) {
//         std::cerr << e.what();
//         return;
//     }
// }

template <typename T1> void iter(T1 *arr, size_t size, void (*func)(T1 &)) {
    if (arr == nullptr) {
        throw std::invalid_argument("T1 can not be a nullptr\n");
    }

    if (size == 0) {
        throw std::invalid_argument("T2 must be more then 0\n");
    }

    try {
        for (size_t i = 0; i < size; i++) {
            if (arr[i] == '\0') { // for c style array's
                return;
            }
            func(arr[i]);
        }
    } catch (std::exception &e) {
        std::cerr << e.what();
        return;
    }
}

#endif // !ITER_HPP
