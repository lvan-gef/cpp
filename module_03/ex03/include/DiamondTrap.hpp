/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   DiamondTrap.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/05 15:48:57 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 22:32:17 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIAMONDTRAP_H
#define DIAMONDTRAP_H

#include <string>

#include "./ClapTrap.hpp"
#include "./FragTrap.hpp"
#include "./ScavTrap.hpp"

class DiamondTrap : public FragTrap, public ScavTrap {
  public:
    DiamondTrap();
    explicit DiamondTrap(const std::string &name);

    DiamondTrap(const DiamondTrap &diamondTrap);
    DiamondTrap &operator=(const DiamondTrap &diamondTrap);

    void whoAmI(void) const;

    // debug/testing
    unsigned int getPoints(void) const;
    unsigned int getEnergy(void) const;
    unsigned int getDamage(void) const;
    std::string getName(void) const;

    ~DiamondTrap();

  private:
    std::string _name;

    // protected:
    //   static unsigned int _points;
    //   static unsigned int _energy;
    //   static unsigned int _damage;
};

#endif
