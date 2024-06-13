/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Dog.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:34:20 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:34:20 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
#define DOG_HPP

#include <iostream>
#include <new>
#include <ostream>
#include <string>

#include "../include/AAnimal.hpp"
#include "../include/Brain.hpp"

class Dog : public AAnimal {
  public:
    Dog();

    Dog(const Dog &rhs);
    Dog &operator=(const Dog &rhs);

    Dog(Dog &&rhs) noexcept;
    Dog &operator=(Dog &&rhs) noexcept;

    void makeSound() const override;
    std::string getType() const override;

    bool add_idea(const std::string &idea);
    void remove_idea(size_t index);
    void remove_idea(const std::string &idea);
    void remove_ideas();

    void print_idea(size_t index) const;
    void print_ideas() const;

    size_t capacity() const;
    size_t len() const;

    ~Dog() override;

  private:
    Brain *brain_;
};

#endif // !DOG_HPP
