/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   AMateria.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:34:52 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:34:52 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMATERIA_HPP
#define AMATERIA_HPP

#include <iostream>
#include <string>

class ICharacter; // Forward declaration

class AMateria {
  public:
    AMateria();
    explicit AMateria(const std::string &type);

    AMateria(const AMateria &rhs);
    AMateria &operator=(const AMateria &rhs);

    AMateria(AMateria &&rhs) noexcept;
    AMateria &operator=(AMateria &&rhs) noexcept;

    std::string const &getType() const;
    virtual AMateria *clone() const = 0;
    virtual void use(ICharacter &target);

    virtual ~AMateria() = 0;

  protected:
    std::string type_;
};

#endif // !AMATERIA_HPP
