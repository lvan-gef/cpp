/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   WrongCat.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:34:20 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:34:20 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGCAT_HPP
#define WRONGCAT_HPP

#include <iostream>
#include <new>
#include <ostream>
#include <string>

#include "../include/Brain.hpp"
#include "../include/WrongAnimal.hpp"

class WrongCat : public WrongAnimal {
  public:
    WrongCat();

    WrongCat(const WrongCat &rhs);
    WrongCat &operator=(const WrongCat &rhs);

    WrongCat(WrongCat &&rhs) noexcept;
    WrongCat &operator=(WrongCat &&rhs) noexcept;

    void makeSound() const override;
    std::string getType() const override;

    bool add_idea(const std::string &idea);
    void remove_idea(size_t index);
    void remove_idea(const std::string &idea);

    void print_idea(size_t index) const;
    void print_ideas() const;

    size_t capacity() const;
    size_t len() const;

    ~WrongCat() override;

  private:
    Brain *brain_;
};

#endif // !WRONGCAT_HPP
