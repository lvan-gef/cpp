/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Cat.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:32:50 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:32:50 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
#define CAT_HPP

#include <iostream>
#include <ostream>
#include <string>

#include "../include/Animal.hpp"

class Cat : public Animal {
  public:
    Cat();

    Cat(const Cat &rhs);
    Cat &operator=(const Cat &rhs);

    Cat(Cat &&rhs) noexcept;
    Cat &operator=(Cat &&rhs) noexcept;

    void makeSound() const override;

    ~Cat() override;
};

#endif // !CAT_HPP
