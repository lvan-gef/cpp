/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   FragTrap.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/05 15:48:51 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 22:32:17 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/FragTrap.hpp"

unsigned int FragTrap::points = 100;
unsigned int FragTrap::energy = 100;
unsigned int FragTrap::damage = 30;

FragTrap::FragTrap() : ClapTrap() {
    std::cout << "Default constructor called for FragTrap with name: " << _name
              << std::endl;
    this->_points = FragTrap::points;
    this->_energy = FragTrap::energy;
    this->_damage = FragTrap::damage;
}

FragTrap::FragTrap(const std::string &name) : ClapTrap(name) {
    std::cout << "Constructor with name called for FragTrap with name: "
              << _name << std::endl;
    this->_name = _name;
    this->_points = FragTrap::points;
    this->_energy = FragTrap::energy;
    this->_damage = FragTrap::damage;
}

FragTrap::FragTrap(const FragTrap &fragTrap) : ClapTrap(fragTrap) {
    std::cout << "Default copy constructor called for FragTrap with name: "
              << _name << std::endl;
    this->_name = fragTrap._name;
    this->_points = fragTrap._points;
    this->_energy = fragTrap._energy;
    this->_damage = fragTrap._damage;
}

FragTrap &FragTrap::operator=(const FragTrap &fragTrap) {
    std::cout
        << "Default copy assignment constructor called for FragTrap with name: "
        << getName() << std::endl;

    if (this != &fragTrap) {
        this->_name = fragTrap._name;
        this->_points = fragTrap._points;
        this->_energy = fragTrap._energy;
        this->_damage = fragTrap._damage;
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
