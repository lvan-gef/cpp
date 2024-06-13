/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Cat.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:34:20 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:34:20 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
#define CAT_HPP

#include <iostream>
#include <new>
#include <ostream>
#include <string>

#include "../include/AAnimal.hpp"
#include "../include/Brain.hpp"

class Cat : public AAnimal {
  public:
    Cat();

    Cat(const Cat &rhs);
    Cat &operator=(const Cat &rhs);

    Cat(Cat &&rhs) noexcept;
    Cat &operator=(Cat &&rhs) noexcept;

    void makeSound() const override;
    std::string getType() const override;

    bool add_idea(const std::string &idea);
    void remove_idea(size_t index);
    void remove_idea(const std::string &idea);

    void print_idea(size_t index) const;
    void print_ideas() const;

    size_t capacity() const;
    size_t len() const;

    ~Cat() override;

  private:
    Brain *brain_;
};

#endif // !CAT_HPP
