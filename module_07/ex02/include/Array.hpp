/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Array.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/23 21:43:42 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/23 21:43:42 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
