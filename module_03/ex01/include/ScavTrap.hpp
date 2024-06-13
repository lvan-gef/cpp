/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ScavTrap.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/05 15:47:58 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 22:32:17 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef scavtrap_h
#define scavtrap_h

#include <string>

#include "./ClapTrap.hpp"

class ScavTrap : public ClapTrap {
  public:
    ScavTrap();
    explicit ScavTrap(const std::string &name);

    ScavTrap(const ScavTrap &scavTrap);
    ScavTrap &operator=(const ScavTrap &scavTrap);

    ~ScavTrap();

    // override the takeDamage method from the parrent
    void attack(const std::string &target);

    void guardGate(void) const;

  private:
};

#endif
