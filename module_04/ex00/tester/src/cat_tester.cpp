/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cat_tester.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:33:20 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:33:20 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.hpp"

static void animal_sound(Cat &ani) {
    std::string output;

    redirectCoutToFile(tmp_output);
    ani.makeSound();
    restoreCout();
    output = readFromFile(tmp_output);
    assert(output == "meauw meauw\n");
    std::remove(tmp_output.c_str());
    output.clear();
}

static void animal_sound(Animal *ani) {
    std::string output;

    redirectCoutToFile(tmp_output);
    ani->makeSound();
    restoreCout();
    output = readFromFile(tmp_output);
    assert(output == "meauw meauw\n");
    std::remove(tmp_output.c_str());
    output.clear();
}

void cat_test() {
    // -------------------------- CREATE TYPES --------------------------
    std::cout << "Create Cat objects" << '\n';
    Animal *animal_cat_ptr = new (std::nothrow) Cat();
    if (animal_cat_ptr == nullptr) {
        std::cerr << "Failed to create a pointer to a Cat" << '\n';
        exit(1);
    }
    std::cout << '\n';

    Cat *cat_cat_ptr = new (std::nothrow) Cat();
    if (cat_cat_ptr == nullptr) {
        std::cerr << "Failed to clone a pointer to a cat" << '\n';
        delete animal_cat_ptr;
        exit(1);
    }
    std::cout << '\n';

    Cat cat = Cat();
    std::cout << '\n';

    Cat cat_copy = cat;
    std::cout << '\n';

    Cat cat_assigment_copy;
    cat_assigment_copy = cat;
    std::cout << '\n';

    // -------------------------- ASSERT DEFAULTS --------------------------
    std::cout << "Asssert default values" << '\n';
    assert(animal_cat_ptr->getType() == "Cat");
    assert(cat_cat_ptr->getType() == "Cat");
    assert(cat.getType() == "Cat");
    assert(cat_copy.getType() == "Cat");
    assert(cat_assigment_copy.getType() == "Cat");

    animal_sound(animal_cat_ptr);
    animal_sound(cat_cat_ptr);
    animal_sound(cat);
    animal_sound(cat_copy);
    animal_sound(cat_assigment_copy);
    std::cout << '\n';

    // -------------------------- DELETE POINTERS --------------------------
    std::cout << "Lets delete the cat_ptr" << '\n';
    delete animal_cat_ptr;
    std::cout << '\n';

    delete cat_cat_ptr;
    std::cout << '\n';

    // -------------------------- MOVE TYPES --------------------------
    std::cout << "move stuff over" << '\n';
    Cat cat_move = std::move(cat);
    std::cout << '\n';

    Cat cat_assigment_move;
    cat_move = std::move(cat_copy);
    std::cout << '\n';

    // -------------------------- ASSERT TYPES--------------------------
    std::cout << "Assert clone and moved objects" << '\n';

    assert(cat.getType() == "");
    assert(cat_copy.getType() == "");
    assert(cat_move.getType() == "Cat");
    assert(cat_assigment_move.getType() == "Cat");

    animal_sound(cat_move);
    animal_sound(cat_assigment_move);

    std::cout << '\n';
}
