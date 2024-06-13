/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Dog.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:32:50 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:32:50 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
#define DOG_HPP

#include <iostream>
#include <ostream>
#include <string>

#include "../include/Animal.hpp"

class Dog : public Animal {
  public:
    Dog();

    Dog(const Dog &rhs);
    Dog &operator=(const Dog &rhs);

    Dog(Dog &&rhs) noexcept;
    Dog &operator=(Dog &&rhs) noexcept;

    void makeSound() const override;

    ~Dog() override;
};

#endif // !DOG_HPP
