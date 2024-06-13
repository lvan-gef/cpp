/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   DiamondTrap.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/05 15:48:51 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/05 15:48:51 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/DiamondTrap.hpp"

DiamondTrap::DiamondTrap() : FragTrap(), ScavTrap() {
  std::cout << "Default constructor called for DiamondTrap with name: " << _name
            << std::endl;
  this->_points = FragTrap::points;
  this->_energy = ScavTrap::energy;
  this->_damage = FragTrap::damage;
}

DiamondTrap::DiamondTrap(const std::string &name)
    : ClapTrap(name), FragTrap(name), ScavTrap(name) {
  this->_name = name;
  this->_points = FragTrap::points;
  this->_energy = ScavTrap::energy;
  this->_damage = FragTrap::damage;
  ClapTrap::_name = name + "_clap_trap";
}

DiamondTrap::DiamondTrap(const DiamondTrap &diamondTrap)
    : ClapTrap(diamondTrap), FragTrap(diamondTrap), ScavTrap(diamondTrap) {
  std::cout << "Default copy constructor called for DiamondTrap with name: "
            << _name << std::endl;
  this->_name = diamondTrap._name;
  this->_points = diamondTrap._points;
  this->_energy = diamondTrap._energy;
  this->_damage = diamondTrap._damage;
}

DiamondTrap &DiamondTrap::operator=(const DiamondTrap &diamondTrap) {
  std::cout << "Default copy assignment constructor called for DiamondTrap "
               "with name: "
            << getName() << std::endl;

  if (this != &diamondTrap) {
    this->_name = diamondTrap._name;
    this->_points = diamondTrap._points;
    this->_energy = diamondTrap._energy;
    this->_damage = diamondTrap._damage;
  }

  return *this;
}

void DiamondTrap::whoAmI(void) const {
  std::cout << "My own name: " << this->_name
            << ", Claptrap name: " << ClapTrap::_name << std::endl;
}

// debug/testing
unsigned int DiamondTrap::getPoints(void) const { return this->_points; }
unsigned int DiamondTrap::getEnergy(void) const { return this->_energy; }
unsigned int DiamondTrap::getDamage(void) const { return this->_damage; }
std::string DiamondTrap::getName(void) const { return this->_name; }

DiamondTrap::~DiamondTrap() {
  std::cout << "Default deconstructor called for DiamondTrap with name: "
            << _name << std::endl;
}
