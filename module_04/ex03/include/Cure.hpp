/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Cure.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:34:52 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:34:52 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_HPP
#define CURE_HPP

#include <iostream>
#include <new>
#include <string>

#include "./AMateria.hpp"
#include "./ICharacter.hpp"

class Cure : public AMateria {
  public:
    Cure();

    Cure(const Cure &rhs);
    Cure &operator=(const Cure &rhs);

    Cure(Cure &&rhs) noexcept;
    Cure &operator=(Cure &&rhs) noexcept;

    AMateria *clone() const override;
    void use(ICharacter &target) override;

    ~Cure() override;
};

#endif // !CURE_HPP
