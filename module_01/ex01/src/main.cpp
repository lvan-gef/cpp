/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 03:05:39 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 21:27:10 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Zombie.hpp"

int main(void) {
    int size;
    Zombie *zombies;

    size = -1;
    std::cout << "Try with " << size << " zombies\n";
    zombies = zombieHorde(-1, "badArmy");
    if (zombies == NULL) {
        std::cout << "-1 zombie army is a bad idea i think...\n";
    } else {
        std::cerr << "uhh.. you should not see this!\n";
    }
    std::cout << "\n";

    size = 10;
    std::cout << "Try with " << size << " zombies without a name\n";
    zombies = zombieHorde(size, " \t\n\r");
    if (zombies == NULL) {
        std::cout
            << "How to give commands to a army if a zombie hase no name??\n";
    } else {
        std::cerr
            << "I'm magic, i can give commands to a army while a zombie hase "
               "no names :)\n";
    }
    std::cout << "\n";
    delete[] zombies;

    std::cout << "Try with " << size << " zombies with a name\n";
    zombies = zombieHorde(size, "works, i hope");
    if (zombies == NULL) {
        std::cerr << "So when you here, i did not expect that... so...\n";
        return (1);
    } else {
        for (int i = 0; i < size; i++) {
            zombies->announce();
        }
        std::cout
            << "I'm magic, i can give commands to a army of zombies while "
               "they all have the same names ;)\n\n";
    }
    delete[] zombies;

    return (0);
}
