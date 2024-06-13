/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wrongcat_tester.cpp                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:34:06 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:34:06 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.hpp"

static void animal_sound(WrongCat &ani) {
    std::string output;

    redirectCoutToFile(tmp_output);
    ani.makeSound();
    restoreCout();
    output = readFromFile(tmp_output);
    assert(output == "iea iea\n");
    std::remove(tmp_output.c_str());
    output.clear();
}

static void animal_sound(WrongAnimal *ani) {
    std::string output;

    redirectCoutToFile(tmp_output);
    ani->makeSound();
    restoreCout();
    output = readFromFile(tmp_output);
    assert(output == "iea iea\n");
    std::remove(tmp_output.c_str());
    output.clear();
}

void wrongcat_test() {
    // -------------------------- CREATE TYPES --------------------------
    std::cout << "Create wrongcat objects" << '\n';
    WrongAnimal *wrongcat_ptr = new (std::nothrow) WrongCat();
    if (wrongcat_ptr == nullptr) {
        std::cerr << "Failed to create a pointer to a wrongcat" << '\n';
        exit(1);
    }
    std::cout << '\n';

    WrongCat *wrongcat_wrongcat_ptr = new (std::nothrow) WrongCat();
    if (wrongcat_wrongcat_ptr == nullptr) {
        std::cerr << "Failed to clone a pointer to a wrongcat" << '\n';
        delete wrongcat_ptr;
        exit(1);
    }
    std::cout << '\n';

    WrongCat wrongcat = WrongCat();
    std::cout << '\n';

    WrongCat wrongcat_copy = wrongcat;
    std::cout << '\n';

    WrongCat wrongcat_assigment_copy;
    wrongcat_assigment_copy = wrongcat;
    std::cout << '\n';

    // -------------------------- ASSERT DEFAULTS --------------------------
    std::cout << "Asssert default values" << '\n';
    assert(wrongcat_ptr->getType() == "WrongCat");
    assert(wrongcat_wrongcat_ptr->getType() == "WrongCat");
    assert(wrongcat.getType() == "WrongCat");
    assert(wrongcat_copy.getType() == "WrongCat");
    assert(wrongcat_assigment_copy.getType() == "WrongCat");

    animal_sound(wrongcat_ptr);
    animal_sound(wrongcat);
    animal_sound(wrongcat_copy);
    animal_sound(wrongcat_assigment_copy);
    std::cout << '\n';

    // -------------------------- DELETE TYPES --------------------------
    std::cout << "Lets delete the wrongcat_ptr" << '\n';
    delete wrongcat_ptr;
    delete wrongcat_wrongcat_ptr;
    std::cout << '\n';

    // -------------------------- DELETE TYPES --------------------------
    std::cout << "move stuff over" << '\n';
    WrongCat wrongcat_move = std::move(wrongcat);
    std::cout << '\n';

    WrongCat wrongcat_assigment_move;
    wrongcat_assigment_move = std::move(wrongcat_copy);
    std::cout << '\n';

    // -------------------------- USE CLONES --------------------------
    std::cout << "Assert clone and moved objects" << '\n';
    assert(wrongcat.getType() == "");
    assert(wrongcat_copy.getType() == "");
    assert(wrongcat_move.getType() == "WrongCat");
    assert(wrongcat_assigment_move.getType() == "WrongCat");

    animal_sound(wrongcat_move);
    animal_sound(wrongcat_assigment_move);
    std::cout << '\n';
}
