/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   HumanB.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/21 03:46:57 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/01/24 15:42:39 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HumanB_h
#define HumanB_h

#include "Weapon.hpp"
#include <iostream>
#include <string>

class HumanB {
public:
  HumanB(const std::string &name);

  void attack(void);
  void setWeapon(Weapon &weapon);

  ~HumanB();

private:
  std::string _name;
  Weapon *_weapon;
};

#endif
