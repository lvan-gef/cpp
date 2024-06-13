/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   FragTrap.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/05 15:48:40 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 22:32:17 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap() {
    std::cout << "Default constructor called for FragTrap with name: " << _name
              << std::endl;
    this->_points = 100;
    this->_energy = 100;
    this->_damage = 30;
}

FragTrap::FragTrap(const std::string &name) : ClapTrap(name) {
    std::cout << "Constructor with name called for FragTrap with name: "
              << _name << std::endl;
    this->_name = _name;
    this->_points = 100;
    this->_energy = 100;
    this->_damage = 30;
}

FragTrap::FragTrap(const FragTrap &scavTrap) : ClapTrap(scavTrap) {
    std::cout << "Default copy constructor called for FragTrap with name: "
              << _name << std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &scavTrap) {
    std::cout
        << "Default copy assignment constructor called for FragTrap with name: "
        << getName() << std::endl;

    if (this != &scavTrap) {
        this->_name = scavTrap._name;
        this->_points = scavTrap._points;
        this->_energy = scavTrap._energy;
        this->_damage = scavTrap._damage;
    }

    return *this;
}

void FragTrap::highFivesGuys(void) const {
    if (this->_points > 0) {
        std::cout << "Lets highfives if you have to energy for it..."
                  << std::endl;
    }
}

FragTrap::~FragTrap() {
    std::cout << "Default deconstructor called for FragTrap with name: "
              << this->_name << std::endl;
}
