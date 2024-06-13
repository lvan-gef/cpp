/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Animal.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:33:32 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:33:32 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMALL_HPP
#define ANIMALL_HPP

#include <iostream>
#include <new>
#include <ostream>
#include <string>

class Animal {
  public:
    Animal();
    explicit Animal(std::string name);

    Animal(const Animal &rhs);
    Animal &operator=(const Animal &rhs);

    Animal(Animal &&rhs) noexcept;
    Animal &operator=(Animal &&rhs) noexcept;

    virtual void makeSound() const;
    virtual std::string getType() const;

    virtual ~Animal();

  protected:
    std::string type_;
};

#endif // !ANIMALL_HPP
