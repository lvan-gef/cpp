/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   WrongAnimal.hpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:33:33 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:33:33 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

#include <iostream>
#include <new>
#include <ostream>
#include <string>

class WrongAnimal {
  public:
    WrongAnimal();
    explicit WrongAnimal(std::string name);

    WrongAnimal(const WrongAnimal &rhs);
    WrongAnimal &operator=(const WrongAnimal &rhs);

    WrongAnimal(WrongAnimal &&rhs) noexcept;
    WrongAnimal &operator=(WrongAnimal &&rhs) noexcept;

    virtual void makeSound() const;
    virtual std::string getType() const;

    virtual ~WrongAnimal();

  protected:
    std::string type_;
};

#endif // !WRONGANIMAL_HPP
