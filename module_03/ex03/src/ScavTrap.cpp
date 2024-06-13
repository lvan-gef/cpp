/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ScavTrap.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/05 15:48:51 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/05 15:48:51 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ScavTrap.hpp"

unsigned int ScavTrap::points = 100;
unsigned int ScavTrap::energy = 50;
unsigned int ScavTrap::damage = 20;

ScavTrap::ScavTrap() : ClapTrap() {
  std::cout << "Default constructor called for Scavtrap with name: " << _name
            << std::endl;
  this->_points = ScavTrap::points;
  this->_energy = ScavTrap::energy;
  this->_damage = ScavTrap::damage;
}

ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name) {
  std::cout << "constructor with name called for Scavtrap with name: " << _name
            << std::endl;
  this->_name = _name;
  this->_points = ScavTrap::points;
  this->_energy = ScavTrap::energy;
  this->_damage = ScavTrap::damage;
}

ScavTrap::ScavTrap(const ScavTrap &scavTrap) : ClapTrap(scavTrap) {
  std::cout << "Default copy constructor called for Scavtrap with name: "
            << this->_name << std::endl;
  this->_name = scavTrap._name;
  this->_points = scavTrap._points;
  this->_energy = scavTrap._energy;
  this->_damage = scavTrap._damage;
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
