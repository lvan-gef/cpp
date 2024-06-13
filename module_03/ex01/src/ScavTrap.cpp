/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ScavTrap.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/05 15:48:21 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 22:32:17 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap() {
    std::cout << "Default constructor called for Scavtrap with name: " << _name
              << std::endl;

    this->_points = 100;
    this->_energy = 50;
    this->_damage = 20;
}

ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name) {
    std::cout << "Default constructor with name called for Scavtrap with name: "
              << _name << std::endl;
    this->_name = _name;
    this->_points = 100;
    this->_energy = 50;
    this->_damage = 20;
}

ScavTrap::ScavTrap(const ScavTrap &scavTrap) : ClapTrap(scavTrap) {
    std::cout << "Default copy constructor called for Scavtrap with name: "
              << this->_name << std::endl;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &scavTrap) {
    std::cout
        << "Default copy assignment constructor called for Scavtrap with name: "
        << getName() << std::endl;

    if (this != &scavTrap) {
        this->_name = scavTrap._name;
        this->_points = scavTrap._points;
        this->_energy = scavTrap._energy;
        this->_damage = scavTrap._damage;
    }

    return *this;
}

// override the attack method from the parent
void ScavTrap::attack(const std::string &target) {
    if (this->_energy > 0 && this->_points > 0) {
        std::cout << "ScavTrap " << this->_name << " attacks " << target
                  << " causing " << this->_damage << " points of damage!"
                  << std::endl;
        this->_energy--;
    }
}

void ScavTrap::guardGate(void) const {
    if (this->_points > 0) {
        std::cout << "ScavTrap is a Gate Keeper now" << std::endl;
    }
}

ScavTrap::~ScavTrap() {
    std::cout << "Default deconstructor called for Scavtrap with name: "
              << this->_name << std::endl;
}
