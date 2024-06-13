/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   zombieHorde.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/22 16:39:20 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 21:27:10 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Zombie.hpp"

Zombie *zombieHorde(int N, std::string name) {
    if (N <= 0) {
        return (NULL);
    }

    const std::string trimmedName = trim(name);
    if (trimmedName == "") {
        std::cerr << "A zombie in the army has no name\n";
        return (NULL);
    }

    Zombie *zombies = new (std::nothrow) Zombie[N];
    if (zombies == NULL) {
        std::cerr << "Failed to get memory for my army\n";
        return (NULL);
    }
    std::cout << "\n";

    for (int i = 0; i < N; i++) {
        zombies[i].setName(name);
    }

    return (zombies);
}

std::string trim(const std::string &str) {
    const std::string whitespace = " \t\n\r";

    size_t start = str.find_first_not_of(whitespace);
    if (start == std::string::npos) {
        return ("");
    }

    size_t end = str.find_last_not_of(whitespace);
    return (str.substr(start, (end - start + 1)));
}
