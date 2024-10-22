/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Serializer.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/13 21:16:48 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/22 17:42:38 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Serializer.hpp"

uintptr_t Serializer::serialize(Data *ptr) {
    if (ptr == nullptr) {
        throw std::invalid_argument("Can not be a null pointer");
    }

    return reinterpret_cast<uintptr_t>(ptr);
}

Data *Serializer::deserialize(uintptr_t raw) {
    if (raw == 0) {
        throw std::invalid_argument("Can not be a zero");
    }

    return reinterpret_cast<Data *>(raw);
}
