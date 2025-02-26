/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   easyfind.tpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 17:38:37 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/11/06 01:57:37 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_TPP
#define EASYFIND_TPP

#include <algorithm>
#include <stdexcept>

template <typename T>
void easyfind(T array, int target) {
    static_assert(std::is_same<typename T::value_type, int>::value,
                  "Container must hold integers");

    auto it = std::find(array.begin(), array.end(), target);
    if (it != array.end()) {
        return;
    }

    throw std::invalid_argument("target not found in data set\n");
}

#endif // !EASYFIND_TPP
