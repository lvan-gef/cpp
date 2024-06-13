/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Zombie.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/16 04:45:26 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/01/24 15:42:16 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef Zombie_h
#define Zombie_h

#include <cstddef>
#include <iostream>
#include <string>

class Zombie {
public:
  Zombie();

  void announce(void);
  void setName(std::string name);
  std::string getName(void);

  ~Zombie(void);

private:
  std::string _name;
};

Zombie *zombieHorde(int N, std::string name);
std::string trim(const std::string &str);
#endif
