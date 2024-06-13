/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wronganimal_tester.cpp                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:33:20 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:33:20 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.hpp"

static void animal_sound(WrongAnimal &ani) {
    std::string output;

    redirectCoutToFile(tmp_output);
    ani.makeSound();
    restoreCout();
    output = readFromFile(tmp_output);
    assert(output == "nanana nanana\n");
    std::remove(tmp_output.c_str());
    output.clear();
}

static void animal_sound(WrongAnimal *ani) {
    std::string output;

    redirectCoutToFile(tmp_output);
    ani->makeSound();
    restoreCout();
    output = readFromFile(tmp_output);
    assert(output == "nanana nanana\n");
    std::remove(tmp_output.c_str());
    output.clear();
}

void wronganimal_test() {
    // -------------------------- CREATE TYPES --------------------------
    std::cout << "Create WrongAnimal objects" << '\n';
    WrongAnimal *animal_ptr = new (std::nothrow) WrongAnimal();
    if (animal_ptr == nullptr) {
        std::cerr << "Failed to create a pointer to a WrongAnimal" << '\n';
        exit(1);
    }
    std::cout << '\n';

    WrongAnimal animal = WrongAnimal();
    std::cout << '\n';

    WrongAnimal animal_copy = animal;
    std::cout << '\n';

    WrongAnimal animal_assigment_copy;
    animal_assigment_copy = animal;
    std::cout << '\n';

    // -------------------------- ASSERT DEFAULTS --------------------------
    std::cout << "Asssert default values" << '\n';
    assert(animal_ptr->getType() == "WrongAnimal");
    assert(animal.getType() == "WrongAnimal");
    assert(animal_copy.getType() == "WrongAnimal");
    assert(animal_assigment_copy.getType() == "WrongAnimal");

    animal_sound(animal_ptr);
    animal_sound(animal);
    animal_sound(animal_copy);
    animal_sound(animal_assigment_copy);
    std::cout << '\n';

    // -------------------------- DELETE TYPES --------------------------
    std::cout << "Lets delete the animal_ptr" << '\n';
    delete animal_ptr;
    std::cout << '\n';

    // -------------------------- DELETE TYPES --------------------------
    std::cout << "move stuff over" << '\n';
    WrongAnimal animal_move = std::move(animal);
    std::cout << '\n';
    WrongAnimal animal_assigment_move;
    animal_move = std::move(animal_copy);
    std::cout << '\n';

    // -------------------------- USE CLONES --------------------------
    std::cout << "Assert clone and moved objects" << '\n';
    assert(animal_move.getType() == "WrongAnimal");

    assert(animal_copy.getType() == "");
    assert(animal.getType() == "");
    assert(animal_assigment_move.getType() == "WrongAnimal");

    animal_sound(animal_move);
    animal_sound(animal_assigment_move);
    std::cout << '\n';
}
