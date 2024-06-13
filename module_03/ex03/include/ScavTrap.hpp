/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ScavTrap.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/05 15:48:57 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 22:32:17 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_H
#define SCAVTRAP_H

#include <string>

#include "./ClapTrap.hpp"

class ScavTrap : virtual public ClapTrap {
  public:
    ScavTrap();
    explicit ScavTrap(const std::string &name);

    ScavTrap(const ScavTrap &scavTrap);
    ScavTrap &operator=(const ScavTrap &scavTrap);

    ~ScavTrap();

    // override the takeDamage method from the parrent
    void attack(const std::string &target);

    void guardGate(void) const;

  protected:
    static unsigned int points;
    static unsigned int energy;
    static unsigned int damage;
};

#endif
