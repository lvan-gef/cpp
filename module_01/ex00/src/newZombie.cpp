/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   newZombie.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/16 04:46:58 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 21:27:08 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Zombie.hpp"

Zombie *newZombie(std::string name) {
    Zombie *zombie = new (std::nothrow) Zombie(name);
    if (zombie == NULL) {
        std::cerr << "Failed to create zombie\n";
        return NULL;
    }

    return zombie;
}
