#ifndef ARRAY_TPP
#define ARRAY_TPP

// #include "../include/Array.hpp"

template <typename T>
Array<T>::Array() : data(nullptr), length(0) {}

template <typename T>
Array<T>::Array(unsigned int n) : data(new T[n]), length(n) {}

template <typename T>
Array<T>::Array(const Array &rhs) : data(nullptr), length(rhs.length) {
    if (length > 0) {
        data = new T[length];
        std::copy(rhs.data, rhs.data + length, data);
    }
}

template <typename T>
Array<T> &Array<T>::operator=(const Array &rhs) {
    if (this != &rhs) {
        Array temp(rhs);
        std::swap(data, temp.data);
        std::swap(length, temp.length);
    }

    return *this;
}

template <typename T>
Array<T>::Array(Array &&rhs) noexcept : data(rhs.data), length(rhs.length) {
    rhs.data = nullptr;
    rhs.length = 0;
}

template <typename T>
Array<T> &Array<T>::operator=(Array &&rhs) noexcept {
    if (this != &rhs) {
        delete[] data;
        data = rhs.data;
        length = rhs.length;
        rhs.data = nullptr;
        rhs.length = 0;
    }
    return *this;
}

template <typename T>
T &Array<T>::operator[](unsigned int index) {
    if (index >= length) {
        throw std::out_of_range("Index out of bounds");
    }

    return data[index];
}

template <typename T>
const T &Array<T>::operator[](unsigned int index) const {
    if (index >= length) {
        throw std::out_of_range("Index out of bounds");
    }

    return data[index];
}

template <typename T>
unsigned int Array<T>::size() const {
    return length;
}

template <typename T>
Array<T>::~Array() {
    delete[] data;
}

#endif // !ARRAY_TPP
