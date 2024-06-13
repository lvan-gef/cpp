/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Brain.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:34:20 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/29 20:56:33 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <cstddef>
#include <iostream>
#include <new>

class Brain {
  public:
    Brain();

    Brain(const Brain &rhs);
    Brain &operator=(const Brain &rhs);

    Brain(Brain &&rhs) noexcept;
    Brain &operator=(Brain &&rhs) noexcept;

    bool add_idea(const std::string &idea);
    void remove_idea(size_t index);
    void remove_idea(const std::string &idea);
    void remove_ideas();

    void print_idea(size_t index) const;
    void print_ideas() const;

    size_t capacity() const;
    size_t len() const;

    ~Brain();

  private:
    static const size_t size_ = 100;
    std::string *ideas_;
};

#endif // !BRAIN_HPP
