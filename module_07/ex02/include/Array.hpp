#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>

template <typename T>
class Array {
  public:
    Array();
    explicit Array(unsigned int n);

    Array(const Array &rhs);
    Array &operator=(const Array &rhs);

    Array(Array &&rhs) noexcept;
    Array &operator=(Array &&rhs) noexcept;

    T& operator[](unsigned int index);
    const T& operator[](unsigned int index) const;

    unsigned int size() const;

    ~Array();

  private:
    T *data;
    unsigned int length;
};

#include "../templates/Array.tpp"
#endif // !ARRAY_HPP
