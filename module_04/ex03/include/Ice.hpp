/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Ice.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:34:52 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:34:52 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICE_HPP
#define ICE_HPP

#include <iostream>
#include <new>
#include <string>

#include "./AMateria.hpp"
#include "./ICharacter.hpp"

class Ice : public AMateria {
  public:
    Ice();

    Ice(const Ice &rhs);
    Ice &operator=(const Ice &rhs);

    Ice(Ice &&rhs) noexcept;
    Ice &operator=(Ice &&rhs) noexcept;

    AMateria *clone() const override;
    void use(ICharacter &target) override;

    ~Ice() override;
};

#endif // !ICE_HPP
