/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ClapTrap.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/05 15:47:47 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/05 15:47:47 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ClapTrap.hpp"

ClapTrap::ClapTrap() : _name("default"), _points(10), _energy(10), _damage(0) {
  std::cout << "Default constructor called for Claptrap with name: " << _name
            << std::endl;
}

ClapTrap::ClapTrap(const std::string &name)
    : _name(name), _points(10), _energy(10), _damage(0) {
  std::cout << "Constructor called for Claptrap with name: " << _name
            << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &clapTrap)
    : _name(clapTrap._name), _points(clapTrap._points),
      _energy(clapTrap._energy), _damage(clapTrap._damage) {
  std::cout << "Default copy constructor called for Claptrap with name: "
            << _name << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &clapTrap) {
  std::cout
      << "Default copy assignment constructor called for Claptrap with name: "
      << clapTrap._name << std::endl;

  if (this != &clapTrap) {
    this->_name = clapTrap._name;
    this->_points = clapTrap._points;
    this->_energy = clapTrap._energy;
    this->_damage = clapTrap._damage;
  }

  return *this;
}

void ClapTrap::attack(const std::string &target) {
  if (this->_energy > 0 && this->_points > 0) {
    std::cout << "ClapTrap " << this->_name << " attacks " << target
              << " causing " << this->_damage << " damage!" << std::endl;
    this->_energy--;
    return;
  }
}

void ClapTrap::takeDamage(unsigned int amount) {
  std::cout << "ClapTrap " << this->_name << " has taken " << amount
            << " damage!" << std::endl;

  if (amount > this->_points) {
    this->_points = 0;
  } else {
    this->_points -= amount;
  }
}

void ClapTrap::beRepaired(unsigned int amount) {
  if (this->_energy > 0 && this->_points > 0) {
    std::cout << "ClapTrap " << this->_name << " repaired with " << amount
              << " points" << std::endl;
    this->_energy--;
    this->_points += amount;
    return;
  }
}

unsigned int ClapTrap::getPoints(void) const { return this->_points; }
unsigned int ClapTrap::getEnergy(void) const { return this->_energy; }
unsigned int ClapTrap::getDamage(void) const { return this->_damage; }
std::string ClapTrap::getName(void) const { return this->_name; }

ClapTrap::~ClapTrap() {
  std::cout << "Default deconstructor called for Claptrap with name: "
            << this->_name << std::endl;
}
