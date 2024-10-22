/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Serializer.hpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/13 21:10:14 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/22 14:48:46 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <cstdint>
#include <iostream>

using Data = struct Data {
    std::string name;
    uint8_t age;
    Data *next;
};

class Serializer {
  public:
    Serializer() = delete;

    Serializer(const Serializer &rhs) = delete;
    Serializer &operator=(const Serializer &rhs) = delete;

    Serializer(Serializer &&rhs) noexcept = delete;
    Serializer &operator=(Serializer &&rhs) noexcept = delete;

    static uintptr_t serialize(Data *ptr);
    static Data *deserialize(uintptr_t raw);

    ~Serializer() = delete;
};

#endif // !SERIALIZER_HPP
