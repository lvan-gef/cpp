/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Character.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:34:52 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 22:39:26 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <iostream>
#include <new>
#include <string>

#include "AMateria.hpp"
#include "ICharacter.hpp"

struct AMateriaNode {
    AMateria *materia;
    AMateriaNode *next{};

    AMateriaNode(AMateria *m) : materia(m), next(nullptr) {};
};

class Character : public ICharacter {
  public:
    Character();
    explicit Character(std::string type);

    Character(const Character &rhs);
    Character &operator=(const Character &rhs);

    Character(Character &&rhs) noexcept;
    Character &operator=(Character &&rhs) noexcept;

    std::string const &getName() const override;
    void equip(AMateria *m) override;
    void unequip(int idx) override;
    void use(int idx, ICharacter &target) override;

    size_t size() const;
    size_t len() const;

    ~Character() override;

  private:
    std::string name;
    static const size_t size_ = 4;
    AMateria *materias_[size_];
    AMateriaNode *unequippedHead = nullptr;
};

#endif // !CHARACTER_HPP
