/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/16 04:45:40 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 21:22:57 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Zombie.hpp"

int main(void) {
    Zombie *zombie = newZombie("heap");
    zombie->announce();
    delete zombie;

    randomChump("stack");

    return 0;
}
