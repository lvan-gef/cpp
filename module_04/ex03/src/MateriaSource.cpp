/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   MateriaSource.cpp                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:34:59 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/28 19:01:20 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MateriaSource.hpp"

MateriaSource::MateriaSource() : materias_{} {
    std::cout << "Default constructor for MateriaSource is called" << '\n';
}

MateriaSource::MateriaSource(const MateriaSource &rhs) : materias_{} {
    std::cout << "Default copy constructor for MateriaSource is called" << '\n';

    for (size_t index = 0; index < size_; ++index) {
        if (rhs.materias_[index] != nullptr) {
            materias_[index] = rhs.materias_[index]->clone();
        }
    }
}

MateriaSource &MateriaSource::operator=(const MateriaSource &rhs) {
    std::cout << "Copy assignment operator for MateriaSource is called" << '\n';
    if (this != &rhs) {
        for (size_t index = 0; index < size_; ++index) {
            delete materias_[index];

            if (rhs.materias_[index] != nullptr) {
                materias_[index] = rhs.materias_[index]->clone();
            } else {
                materias_[index] = nullptr;
            }
        }
    }

    return *this;
}

MateriaSource::MateriaSource(MateriaSource &&rhs) noexcept : materias_{} {
    std::cout << "Default move constructor for MateriaSource is called" << '\n';

    for (size_t index = 0; index < size_; ++index) {
        materias_[index] = rhs.materias_[index];
        rhs.materias_[index] = nullptr;
    }
}

MateriaSource &MateriaSource::operator=(MateriaSource &&rhs) noexcept {
    std::cout << "Move assignment operator for MateriaSource is called" << '\n';

    if (this != &rhs) {
        for (auto &materia : materias_) {
            if (materia != nullptr) {
                delete materia;
            }
            materia = nullptr;
        }

        for (size_t index = 0; index < size_; ++index) {
            materias_[index] = rhs.materias_[index];
            rhs.materias_[index] = nullptr;
        }
    }

    return *this;
}

void MateriaSource::learnMateria(AMateria *m) {
    if (m == nullptr) {
        return;
    }

    for (auto &materia : materias_) {
        if (materia == nullptr) {
            materia = m->clone();
            if (materia == nullptr) {
                std::cerr << "Failed to learn a Materia" << '\n';
                return;
            }
            return;
        }
    }
}

AMateria *MateriaSource::createMateria(std::string const &type) {
    if (type == "ice" or type == "cure") {
        for (auto &materia : materias_) {
            if (materia != nullptr and materia->getType() == type) {
                return materia->clone();
            }
        }
    }

    return nullptr;
}

size_t MateriaSource::size() const { return size_; }

size_t MateriaSource::len() const {
    size_t counter = 0;

    for (auto materia : materias_) {
        if (materia != nullptr) {
            counter++;
        }
    }
    return counter;
}

MateriaSource::~MateriaSource() {
    std::cout << "Default destructor for MateriaSource is called" << '\n';

    for (auto &materia : materias_) {
        delete materia;
        materia = nullptr;
    }
}
