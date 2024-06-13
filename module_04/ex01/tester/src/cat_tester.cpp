/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cat_tester.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:34:06 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/29 20:52:55 by lvan-gef      ########   odam.nl         */
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

    add_ideas_test(*cat_cat_ptr);
    add_ideas_test(cat);
    add_ideas_test(cat_copy);
    add_ideas_test(cat_assigment_copy);

    remove_ideas_test(*cat_cat_ptr);
    remove_ideas_test(cat);
    remove_ideas_test(cat_copy);
    remove_ideas_test(cat_assigment_copy);
    std::cout << '\n';

    // -------------------------- DELETE POINTERS --------------------------
    std::cout << "Lets delete the base ptr" << '\n';
    delete animal_cat_ptr;
    std::cout << '\n';

    add_ideas_test(*cat_cat_ptr);
    delete cat_cat_ptr;
    std::cout << '\n';

    // -------------------------- MOVE TYPES --------------------------
    add_ideas_test(cat);
    add_ideas_test(cat_copy);
    std::cout << "move stuff over" << '\n';
    Cat cat_move = std::move(cat);
    std::cout << '\n';

    Cat cat_assigment_move;
    cat_assigment_move = std::move(cat_copy);
    std::cout << '\n';

    // -------------------------- ASSERT TYPES--------------------------
    std::cout << "Assert clone and moved objects" << '\n';

    assert(cat.getType() == "");
    assert(cat_copy.getType() == "");
    assert(cat_move.getType() == "Cat");
    assert(cat_assigment_move.getType() == "Cat");

    animal_sound(cat_move);
    animal_sound(cat_assigment_move);

    remove_ideas_test(cat_move);
    remove_ideas_test(cat_assigment_move);

    add_ideas_test(cat_move);
    add_ideas_test(cat_assigment_move);
    std::cout << '\n';
}
