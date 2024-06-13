/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   MateriaSource.hpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:34:52 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:34:52 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include <iostream>
#include <string>

#include "AMateria.hpp"
#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource {
  public:
    MateriaSource();

    MateriaSource(const MateriaSource &rhs);
    MateriaSource &operator=(const MateriaSource &rhs);

    MateriaSource(MateriaSource &&rhs) noexcept;
    MateriaSource &operator=(MateriaSource &&rhs) noexcept;

    void learnMateria(AMateria *) override;
    AMateria *createMateria(std::string const &type) override;

    size_t size() const;
    size_t len() const;
    ~MateriaSource();

  private:
    static const size_t size_ = 4;
    AMateria *materias_[size_];
};

#endif // !MATERIASOURCE_HPP
