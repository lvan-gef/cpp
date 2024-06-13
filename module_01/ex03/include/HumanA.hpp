/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   HumanA.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/21 03:46:57 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/01/24 15:42:39 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HumanA_h
#define HumanA_h

#include "Weapon.hpp"
#include <iostream>
#include <string>

class HumanA {
public:
  HumanA(const std::string &name, Weapon &weapon);

  void attack(void);

  ~HumanA();

private:
  std::string _name;
  Weapon &_weapon;
};

#endif
