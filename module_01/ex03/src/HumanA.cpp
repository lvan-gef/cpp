/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   HumanA.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/21 03:46:35 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/01/24 15:42:49 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/HumanA.hpp"

HumanA::HumanA(const std::string &name, Weapon &weapon)
    : _name(name), _weapon(weapon) {}

void HumanA::attack(void) {
  std::cout << this->_name << " attacks with their " << this->_weapon.getType()
            << "\n";
}

HumanA::~HumanA() {}
