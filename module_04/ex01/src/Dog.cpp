/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Dog.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:33:41 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/29 20:53:52 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Dog.hpp"

Dog::Dog() : Animal("Dog"), brain_(new Brain()) {
    std::cout << "Default constructor for Dog is called" << '\n';
}

Dog::Dog(const Dog &rhs) : Animal(rhs), brain_(new Brain(*rhs.brain_)) {
    std::cout << "Default copy constructor for Dog is called" << '\n';
}

Dog &Dog::operator=(const Dog &rhs) {
    std::cout << "Copy assignment constructor for Dog is called" << '\n';

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

Dog::Dog(Dog &&rhs) noexcept : Animal(std::move(rhs)), brain_(rhs.brain_) {
    std::cout << "Default move constructor for Dog is called" << '\n';
    rhs.brain_ = nullptr;
}

Dog &Dog::operator=(Dog &&rhs) noexcept {
    std::cout << "Move assignment operator for Dog is called" << '\n';

    if (this != &rhs) {
        Animal::operator=(std::move(rhs));

        delete brain_;
        brain_ = rhs.brain_;
        rhs.brain_ = nullptr;
    }

    return *this;
}

void Dog::makeSound() const { std::cout << "woef woef" << '\n'; }

bool Dog::add_idea(const std::string &idea) { return brain_->add_idea(idea); };
void Dog::remove_idea(size_t index) { brain_->remove_idea(index); }
void Dog::remove_idea(const std::string &idea) { brain_->remove_idea(idea); };

void Dog::print_idea(size_t index) const { brain_->print_idea(index); };
void Dog::print_ideas() const { brain_->print_ideas(); };

size_t Dog::capacity() const { return brain_->capacity(); };
size_t Dog::len() const { return brain_->len(); };

Dog::~Dog() {
    std::cout << "Default destructor for Dog is called" << '\n';
    delete brain_;
}
