/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Zombie.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/16 04:45:26 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/01/24 15:41:49 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef Zombie_h
#define Zombie_h

#include <iostream>
#include <new>
#include <string>

class Zombie {
public:
  explicit Zombie(std::string name);
  void announce(void);
  ~Zombie(void);

private:
  std::string _name;
};

Zombie *newZombie(std::string name);
void randomChump(std::string name);

#endif
