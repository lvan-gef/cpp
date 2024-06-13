/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   FragTrap.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/05 15:48:57 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/05 15:48:57 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_H
#define FRAGTRAP_H

#include <string>

#include "./ClapTrap.hpp"

class FragTrap : virtual public ClapTrap {
public:
  FragTrap();
  explicit FragTrap(const std::string &name);

  FragTrap(const FragTrap &fragTrap);
  FragTrap &operator=(const FragTrap &fragTrap);

  ~FragTrap();

  void highFivesGuys(void) const;

  // unsigned int getPoints(void) const;
  // unsigned int getEnergy(void) const;
  // unsigned int getDamage(void) const;

protected:
  static unsigned int points;
  static unsigned int energy;
  static unsigned int damage;
};

#endif
