/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Cat.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:33:41 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/29 20:51:01 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cat.hpp"

Cat::Cat() : Animal("Cat"), brain_(new Brain()) {
    std::cout << "Default constructor for Cat is called" << '\n';
}

Cat::Cat(const Cat &rhs) : Animal(rhs), brain_(new Brain(*rhs.brain_)) {
    std::cout << "Default copy constructor for Cat is called" << '\n';
}

Cat &Cat::operator=(const Cat &rhs) {
    std::cout << "Copy assignment constructor for Cat is called" << '\n';

    if (this != &rhs) {
        try {
            Animal::operator=(rhs);

            Brain *newBrain = new Brain(*rhs.brain_);
            delete brain_;
            brain_ = newBrain;
        } catch (std::bad_alloc &) {
            throw;
        }
    }

    return *this;
}

Cat::Cat(Cat &&rhs) noexcept : Animal(std::move(rhs)), brain_(rhs.brain_) {
    std::cout << "Default move constructor for Cat is called" << '\n';
    rhs.brain_ = nullptr;
}

Cat &Cat::operator=(Cat &&rhs) noexcept {
    std::cout << "Move assignment operator for Cat is called" << '\n';

    if (this != &rhs) {
        Animal::operator=(std::move(rhs));

        delete brain_;
        brain_ = rhs.brain_;
        rhs.brain_ = nullptr;
    }

    return *this;
}

void Cat::makeSound() const { std::cout << "meauw meauw" << '\n'; }

bool Cat::add_idea(const std::string &idea) { return brain_->add_idea(idea); };
void Cat::remove_idea(size_t index) { brain_->remove_idea(index); }
void Cat::remove_idea(const std::string &idea) { brain_->remove_idea(idea); };

void Cat::print_idea(size_t index) const { brain_->print_idea(index); };
void Cat::print_ideas() const { brain_->print_ideas(); };

size_t Cat::capacity() const { return brain_->capacity(); };
size_t Cat::len() const { return brain_->len(); };

Cat::~Cat() {
    std::cout << "Default destructor for Cat is called" << '\n';
    delete brain_;
}
