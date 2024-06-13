/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   FragTrap.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/05 15:48:33 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 22:32:17 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_H
#define FRAGTRAP_H

#include <string>

#include "./ClapTrap.hpp"

class FragTrap : public ClapTrap {
  public:
    FragTrap();
    explicit FragTrap(const std::string &name);

    FragTrap(const FragTrap &fragTrap);
    FragTrap &operator=(const FragTrap &fragTrap);

    ~FragTrap();

    void highFivesGuys(void) const;
};

#endif
