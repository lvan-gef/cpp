/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   WrongCat.cpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:34:28 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/29 20:57:24 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/WrongCat.hpp"

WrongCat::WrongCat() : WrongAnimal("WrongCat"), brain_(new Brain()) {
    std::cout << "Default constructor for WrongCat is called" << '\n';
}

WrongCat::WrongCat(const WrongCat &rhs)
    : WrongAnimal(rhs), brain_(new Brain(*rhs.brain_)) {
    std::cout << "Default copy constructor for WrongCat is called" << '\n';
}

WrongCat &WrongCat::operator=(const WrongCat &rhs) {
    std::cout << "Copy assignment constructor for WrongCat is called" << '\n';

    if (this != &rhs) {
        try {
            WrongAnimal::operator=(rhs);

            Brain *newBrain = new Brain(*rhs.brain_);
            delete brain_;
            brain_ = newBrain;
        } catch (std::bad_alloc &) {
            throw;
        }
    }

    return *this;
}

WrongCat::WrongCat(WrongCat &&rhs) noexcept
    : WrongAnimal(std::move(rhs)), brain_(rhs.brain_) {
    std::cout << "Default move constructor for WrongCat is called" << '\n';
    rhs.brain_ = nullptr;
}

WrongCat &WrongCat::operator=(WrongCat &&rhs) noexcept {
    std::cout << "Move assignment operator for WrongCat is called" << '\n';

    if (this != &rhs) {
        WrongAnimal::operator=(std::move(rhs));

        delete brain_;
        brain_ = rhs.brain_;
        rhs.brain_ = nullptr;
    }

    return *this;
}

void WrongCat::makeSound() const { std::cout << "iea iea" << '\n'; }
std::string WrongCat::getType() const { return type_; };

bool WrongCat::add_idea(const std::string &idea) {
    return brain_->add_idea(idea);
};
void WrongCat::remove_idea(size_t index) { brain_->remove_idea(index); }
void WrongCat::remove_idea(const std::string &idea) {
    brain_->remove_idea(idea);
};

void WrongCat::print_idea(size_t index) const { brain_->print_idea(index); };
void WrongCat::print_ideas() const { brain_->print_ideas(); };

size_t WrongCat::capacity() const { return brain_->capacity(); };
size_t WrongCat::len() const { return brain_->len(); };

WrongCat::~WrongCat() {
    std::cout << "Default destructor for WrongCat is called" << '\n';
    delete brain_;
}
