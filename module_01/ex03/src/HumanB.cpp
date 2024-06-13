/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   HumanB.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/21 03:46:49 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 21:27:10 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/HumanB.hpp"

HumanB::HumanB(const std::string &name) : _name(name) {
    HumanB::_weapon = NULL;
}

void HumanB::attack(void) {
    if (HumanB::_weapon == NULL) {
        std::cerr << this->_name << " has no weapon to attack...\n";
        return;
    }
    std::cout << this->_name << " attacks with their "
              << this->_weapon->getType() << "\n";
}

void HumanB::setWeapon(Weapon &weapon) { this->_weapon = &weapon; }

HumanB::~HumanB() {}
