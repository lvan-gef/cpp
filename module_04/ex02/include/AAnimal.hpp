/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   AAnimal.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:34:20 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:34:20 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMALL_HPP
#define ANIMALL_HPP

#include <iostream>
#include <new>
#include <ostream>
#include <string>

class AAnimal {
  public:
    AAnimal();
    explicit AAnimal(std::string name);

    AAnimal(const AAnimal &rhs);
    AAnimal &operator=(const AAnimal &rhs);

    AAnimal(AAnimal &&rhs) noexcept;
    AAnimal &operator=(AAnimal &&rhs) noexcept;

    virtual std::string getType() const = 0;
    virtual void makeSound() const = 0;

    virtual ~AAnimal();

  protected:
    std::string type_;
};

#endif // !ANIMALL_HPP
