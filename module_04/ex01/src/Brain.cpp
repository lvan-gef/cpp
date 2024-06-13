/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Brain.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:33:41 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/29 20:49:18 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Brain.hpp"

Brain::Brain() : ideas_(new std::string[size_]) {
    std::cout << "Default constructor for Brain is called" << '\n';
}

Brain::Brain(const Brain &rhs) : ideas_(new std::string[size_]) {
    std::cout << "Default copy constructor for Brain is called" << '\n';
    for (size_t index = 0; index < size_; ++index) {
        ideas_[index] = rhs.ideas_[index];
    }
}

Brain &Brain::operator=(const Brain &rhs) {
    std::cout << "Default copy assignment constructor for Brain is called"
              << '\n';

    if (this != &rhs) {
        std::string *newIdeas = nullptr;
        try {
            newIdeas = new std::string[size_];

            for (size_t index = 0; index < size_; ++index) {
                newIdeas[index] = rhs.ideas_[index];
            }

            delete[] ideas_;
            ideas_ = newIdeas;
        } catch (const std::bad_alloc &) {
            delete[] newIdeas;
            throw;
        }
    }
    return *this;
}

Brain::Brain(Brain &&rhs) noexcept : ideas_(rhs.ideas_) {
    std::cout << "Default move constructor for Brain is called" << '\n';
    rhs.ideas_ = nullptr;
}

Brain &Brain::operator=(Brain &&rhs) noexcept {
    std::cout << "Default move assignment operator for Brain is called" << '\n';

    if (this != &rhs) {
        delete[] ideas_;

        ideas_ = rhs.ideas_;
        rhs.ideas_ = nullptr;
    }

    return *this;
}

bool Brain::add_idea(const std::string &idea) {
    if (idea.empty()) {
        return false;
    }

    for (size_t index = 0; index < size_; ++index) {
        if (ideas_[index].empty()) {
            ideas_[index] = idea;
            return true;
        }
    }

    return false;
}

void Brain::remove_idea(size_t index) {
    if (index >= size_) {
        return;
    }

    ideas_[index].clear();
    return;
}

void Brain::remove_idea(const std::string &idea) {
    for (size_t index = 0; index < size_; ++index) {
        if (ideas_[index] == idea) {
            ideas_[index].clear();
            return;
        }
    }
}

void Brain::print_idea(size_t index) const {
    if (index >= size_) {
        return;
    }

    if (!ideas_[index].empty()) {
        std::cout << ideas_[index] << '\n';
    }
}

void Brain::print_ideas() const {
    for (size_t index = 0; index < size_; ++index) {
        if (!ideas_[index].empty()) {
            std::cout << ideas_[index] << '\n';
        }
    }
}

size_t Brain::capacity() const { return size_; }

size_t Brain::len() const {
    size_t len = 0;

    for (size_t index = 0; index < size_; ++index) {
        if (!ideas_[index].empty()) {
            len++;
        }
    }

    return len;
}

Brain::~Brain() {
    std::cout << "Default destructor for Brain is called" << '\n';
    delete[] ideas_;
}
