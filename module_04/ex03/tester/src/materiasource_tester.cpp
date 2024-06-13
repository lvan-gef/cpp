/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   materiasource_tester.cpp                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:35:10 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/28 19:05:57 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.hpp"

static void materiasource_learn_materias_test(MateriaSource *ms) {
    size_t cur_len = ms->len();
    ms->learnMateria(nullptr);
    assert(ms->len() == cur_len);

    for (size_t index = 0; index < ms->size(); ++index) {
        if (index % 2) {
            redirectCoutToFile(tmp_output);
            Ice *tmp_ice = new Ice();
            restoreCout();
            std::remove(tmp_output.c_str());

            ms->learnMateria(tmp_ice);

            redirectCoutToFile(tmp_output);
            restoreCout();
			delete tmp_ice;
            std::remove(tmp_output.c_str());
        } else {
            redirectCoutToFile(tmp_output);
            Cure *tmp_cure = new Cure();
            restoreCout();
            std::remove(tmp_output.c_str());

            ms->learnMateria(tmp_cure);

            redirectCoutToFile(tmp_output);
            restoreCout();
            std::remove(tmp_output.c_str());
			delete tmp_cure;
        }
    }
    assert(ms->len() == ms->size());

    Ice tmp_ice = Ice();
    ms->learnMateria(&tmp_ice);
    assert(ms->len() == ms->size());
}

static void materiasource_learn_materias_test(MateriaSource &ms) {
    size_t cur_len = ms.len();
    ms.learnMateria(nullptr);
    assert(ms.len() == cur_len);

    for (size_t index = 0; index < ms.size(); ++index) {
        if (index % 2) {
            redirectCoutToFile(tmp_output);
            Ice *tmp_ice = new Ice();
            restoreCout();
            std::remove(tmp_output.c_str());

            ms.learnMateria(tmp_ice);

            redirectCoutToFile(tmp_output);
            restoreCout();
			delete tmp_ice;
            std::remove(tmp_output.c_str());
        } else {
            redirectCoutToFile(tmp_output);
            Cure *tmp_cure = new Cure();
            restoreCout();
            std::remove(tmp_output.c_str());

            ms.learnMateria(tmp_cure);

            redirectCoutToFile(tmp_output);
            restoreCout();
            std::remove(tmp_output.c_str());
			delete tmp_cure;
        }
    }
    assert(ms.len() == ms.size());

    Ice *tmp_ice = new Ice();
    ms.learnMateria(tmp_ice);
    assert(ms.len() == ms.size());
	delete tmp_ice;
}

static void materiasource_create_materias_test(MateriaSource *ms) {
    try {
        redirectCoutToFile(tmp_output);
        AMateria *cloned_materia = ms->createMateria("nanana");
        restoreCout();
        std::remove(tmp_output.c_str());

        assert(cloned_materia == nullptr);

        redirectCoutToFile(tmp_output);
        delete cloned_materia;
        restoreCout();
        std::remove(tmp_output.c_str());
    } catch (std::bad_alloc &) {
        std::cerr << "Failed to clone a Materia" << '\n';
        throw;
    }

    for (size_t index = 0; index < ms->size(); ++index) {
        try {
            if (index % 2) {
                redirectCoutToFile(tmp_output);
                AMateria *cloned_materia = ms->createMateria("ice");
                restoreCout();
                std::remove(tmp_output.c_str());

                assert(cloned_materia != nullptr);

                redirectCoutToFile(tmp_output);
                delete cloned_materia;
                restoreCout();
                std::remove(tmp_output.c_str());
            } else {
                redirectCoutToFile(tmp_output);
                AMateria *cloned_materia = ms->createMateria("ice");
                restoreCout();
                std::remove(tmp_output.c_str());

                assert(cloned_materia != nullptr);

                redirectCoutToFile(tmp_output);
                delete cloned_materia;
                restoreCout();
                std::remove(tmp_output.c_str());
            }
        } catch (std::bad_alloc &) {
            std::cerr << "Failed to clone a Materia" << '\n';
            throw;
        }
    }
}

static void materiasource_create_materias_test(MateriaSource &ms) {
    try {
        redirectCoutToFile(tmp_output);
        AMateria *cloned_materia = ms.createMateria("nanana");
        restoreCout();
        std::remove(tmp_output.c_str());

        assert(cloned_materia == nullptr);

        redirectCoutToFile(tmp_output);
        delete cloned_materia;
        restoreCout();
        std::remove(tmp_output.c_str());
    } catch (std::bad_alloc &) {
        std::cerr << "Failed to clone a Materia" << '\n';
        throw;
    }

    for (size_t index = 0; index < ms.size(); ++index) {
        try {
            if (index % 2) {
                redirectCoutToFile(tmp_output);
                AMateria *cloned_materia = ms.createMateria("ice");
                restoreCout();
                std::remove(tmp_output.c_str());

                assert(cloned_materia != nullptr);

                redirectCoutToFile(tmp_output);
                delete cloned_materia;
                restoreCout();
                std::remove(tmp_output.c_str());
            } else {
                redirectCoutToFile(tmp_output);
                AMateria *cloned_materia = ms.createMateria("ice");
                restoreCout();
                std::remove(tmp_output.c_str());

                assert(cloned_materia != nullptr);

                redirectCoutToFile(tmp_output);
                delete cloned_materia;
                restoreCout();
                std::remove(tmp_output.c_str());
            }
        } catch (std::bad_alloc &) {
            std::cerr << "Failed to clone a Materia" << '\n';
            throw;
        }
    }
}

void materiasource_test() {
    // -------------------------- CREATE TYPES --------------------------
    std::cout << "Create MateriaSource objects" << '\n';
    MateriaSource materiasource = MateriaSource();
    std::cout << '\n';

    MateriaSource *materiasource_ptr = new MateriaSource();
    std::cout << '\n';

    MateriaSource materiasource_copy = materiasource;
    std::cout << '\n';

    MateriaSource materiasource_assigment_copy;
    materiasource_assigment_copy = materiasource_copy;
    std::cout << '\n';

    // -------------------------- ASSERT DEFAULTS --------------------------
    std::cout << "Asssert default values" << '\n';
    assert(materiasource.len() == 0);
    assert(materiasource_ptr->len() == 0);
    assert(materiasource_copy.len() == 0);
    assert(materiasource_assigment_copy.len() == 0);
    std::cout << '\n';

    // -------------------------- TEST METHODS --------------------------
    std::cout << "Learn Materia's" << '\n';
    materiasource_learn_materias_test(materiasource);
    materiasource_learn_materias_test(materiasource_ptr);
    materiasource_learn_materias_test(materiasource_copy);
    materiasource_learn_materias_test(materiasource_assigment_copy);
    std::cout << '\n';

    std::cout << "create Materia's" << '\n';
    materiasource_create_materias_test(materiasource);
    materiasource_create_materias_test(materiasource_ptr);
    materiasource_create_materias_test(materiasource_copy);
    materiasource_create_materias_test(materiasource_assigment_copy);
    std::cout << '\n';

    // -------------------------- MOVE TYPES --------------------------
    std::cout << "move stuff over" << '\n';
    MateriaSource materiasource_move = std::move(materiasource);
    std::cout << '\n';

    MateriaSource materiasource_assigment_move;
    materiasource_assigment_move = std::move(materiasource_copy);
    std::cout << '\n';

    // -------------------------- ASSERT TYPES--------------------------
    std::cout << "Assert clone and moved objects" << '\n';
    assert(materiasource.len() == 0);
    assert(materiasource_copy.len() == 0);
    assert(materiasource_move.len() == materiasource_move.size());
    assert(materiasource_assigment_move.len() ==
           materiasource_assigment_move.size());

    materiasource_learn_materias_test(materiasource_move);
    materiasource_learn_materias_test(materiasource_assigment_move);

    materiasource_create_materias_test(materiasource_move);
    materiasource_create_materias_test(materiasource_assigment_move);

    std::cout << '\n';

    // -------------------------- DELETE TYPES--------------------------
    std::cout << "delete all types" << '\n';
    delete materiasource_ptr;
}
