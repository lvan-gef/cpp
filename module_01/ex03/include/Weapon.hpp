/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Weapon.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/21 03:46:57 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/01/24 15:42:39 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef Weapon_h
#define Weapon_h

#include <string>

class Weapon {
public:
  Weapon(const std::string &type);

  const std::string &getType(void);
  void setType(const std::string &newType);

  ~Weapon();

private:
  std::string _type;
};

#endif
