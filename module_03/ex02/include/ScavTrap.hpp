/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ScavTrap.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/05 15:48:33 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/05 15:48:33 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_H
#define SCAVTRAP_H

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
