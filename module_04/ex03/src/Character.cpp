/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Character.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:34:59 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/29 18:39:36 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Character.hpp"
#include <new>

Character::Character() : name("Default"), materias_{} {
    std::cout << "Default constructor for Character is called" << '\n';
}

Character::Character(std::string type) : name(std::move(type)), materias_{} {
    std::cout << "Name constructor for Character is called" << '\n';
}

Character::Character(const Character &rhs) : name(rhs.name), materias_{} {
    std::cout << "Default copy operator for Character is called" << '\n';

    for (size_t index = 0; index < size_; ++index) {
        if (rhs.materias_[index] != nullptr) {
            materias_[index] = rhs.materias_[index]->clone();
            if (materias_[index] == nullptr) {
                throw std::bad_alloc();
            }
        }
    }
}

Character &Character::operator=(const Character &rhs) {
    std::cout << "Copy assigment operator for Character is called" << '\n';

    if (this != &rhs) {
        for (auto &materia : materias_) {
            delete materia;
            materia = nullptr;
        }

        for (size_t index = 0; index < size_; ++index) {
            if (rhs.materias_[index] != nullptr) {
                materias_[index] = rhs.materias_[index]->clone();
                if (materias_[index] == nullptr) {
                    throw std::bad_alloc();
                }
            } else {
                materias_[index] = nullptr;
            }
        }
        name = rhs.name;
    }

    return *this;
}

Character::Character(Character &&rhs) noexcept
    : name(std::move(rhs.name)), materias_{} {
    std::cout << "Default move constructor for Character is called" << '\n';

    for (size_t index = 0; index < size_; ++index) {
        materias_[index] = rhs.materias_[index];
        rhs.materias_[index] = nullptr;
    }

    rhs.name.clear();
}

Character &Character::operator=(Character &&rhs) noexcept {
    std::cout << "Move assignment operator for Character is called" << '\n';
    if (this != &rhs) {
        name = std::move(rhs.name);
        rhs.name.clear();

        for (size_t index = 0; index < size_; ++index) {
            materias_[index] = rhs.materias_[index];
            rhs.materias_[index] = nullptr;
        }
    }

    return *this;
}

std::string const &Character::getName() const { return name; }

void Character::equip(AMateria *m) {
    for (auto &materia : materias_) {
        if (materia == nullptr) {
            materia = m;
            return;
        }
    }
}

void Character::unequip(int idx) {
    if (idx < 0 || idx > 3) {
        return;
    }

    if (materias_[idx] != nullptr) {
        AMateriaNode *newNode = new (std::nothrow) AMateriaNode(materias_[idx]);
        if (newNode == nullptr) {
            return;
        }
        newNode->next = unequippedHead;
        unequippedHead = newNode;
        materias_[idx] = nullptr;
    }
}

void Character::use(int idx, ICharacter &target) {
    if (idx < 0 || idx > 3) {
        return;
    }

    if (materias_[idx] == nullptr) {
        return;
    }

    materias_[idx]->use(target);
}

size_t Character::size() const { return size_; }

size_t Character::len() const {
    size_t counter = 0;

    for (auto materia : materias_) {
        if (materia != nullptr) {
            counter++;
        }
    }

    return counter;
}

Character::~Character() {
    std::cout << "Default destructor for Character is called" << '\n';
    for (auto &materia : materias_) {
        delete materia;
        materia = nullptr;
    }

    AMateriaNode *current = unequippedHead;
    while (current != nullptr) {
        AMateriaNode *next = current->next;
        delete current->materia;
        delete current;
        current = next;
    }
}
