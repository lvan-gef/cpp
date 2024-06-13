/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   WrongCat.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:32:50 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:32:50 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGCAT_HPP
#define WRONGCAT_HPP

#include <iostream>
#include <ostream>
#include <string>

#include "../include/WrongAnimal.hpp"

class WrongCat : public WrongAnimal {
  public:
    WrongCat();

    WrongCat(const WrongCat &rhs);
    WrongCat &operator=(const WrongCat &rhs);

    WrongCat(WrongCat &&rhs) noexcept;
    WrongCat &operator=(WrongCat &&rhs) noexcept;

    void makeSound() const override;

    ~WrongCat() override;
};

#endif // !WRONGCAT_HPP
