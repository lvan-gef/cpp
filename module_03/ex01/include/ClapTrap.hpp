/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ClapTrap.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/05 15:47:58 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 22:32:17 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef claptrap_h
#define claptrap_h

#include <iostream>
#include <string>

class ClapTrap {
  public:
    ClapTrap();
    explicit ClapTrap(const std::string &name);
    ClapTrap(const ClapTrap &clapTrap);
    ClapTrap &operator=(const ClapTrap &clapTrap);

    void attack(const std::string &target);
    void takeDamage(unsigned int amount);
    void beRepaired(unsigned int amount);

    // debug/test
    unsigned int getPoints(void) const;
    unsigned int getEnergy(void) const;
    unsigned int getDamage(void) const;
    std::string getName(void) const;

    ~ClapTrap();

  protected:
    std::string _name;
    unsigned int _points;
    unsigned int _energy;
    unsigned int _damage;
};

#endif
