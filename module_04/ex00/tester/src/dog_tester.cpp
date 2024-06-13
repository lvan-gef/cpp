/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dog_tester.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:33:20 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:33:20 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.hpp"

static void animal_sound(Dog &ani) {
    std::string output;

    redirectCoutToFile(tmp_output);
    ani.makeSound();
    restoreCout();
    output = readFromFile(tmp_output);
    assert(output == "woef woef\n");
    std::remove(tmp_output.c_str());
    output.clear();
}

static void animal_sound(Animal *ani) {
    std::string output;

    redirectCoutToFile(tmp_output);
    ani->makeSound();
    restoreCout();
    output = readFromFile(tmp_output);
    assert(output == "woef woef\n");
    std::remove(tmp_output.c_str());
    output.clear();
}

void dog_test() {
    // -------------------------- CREATE TYPES --------------------------
    std::cout << "Create Dog objects" << '\n';
    Animal *animal_dog_ptr = new (std::nothrow) Dog();
    if (animal_dog_ptr == nullptr) {
        std::cerr << "Failed to create a pointer to a Animal Dog" << '\n';
        exit(1);
    }
    std::cout << '\n';

    Dog *dog_dog_ptr = new (std::nothrow) Dog();
    if (dog_dog_ptr == nullptr) {
        std::cerr << "Failed to clone a pointer to a Dog" << '\n';
        delete animal_dog_ptr;
        exit(1);
    }
    std::cout << '\n';

    Dog dog = Dog();
    std::cout << '\n';

    Dog dog_copy = dog;
    std::cout << '\n';

    Dog dog_assigment_copy;
    dog_assigment_copy = dog;
    std::cout << '\n';

    // -------------------------- ASSERT DEFAULTS --------------------------
    std::cout << "Asssert default values" << '\n';
    assert(animal_dog_ptr->getType() == "Dog");
    assert(dog_dog_ptr->getType() == "Dog");
    assert(dog.getType() == "Dog");
    assert(dog_copy.getType() == "Dog");
    assert(dog_assigment_copy.getType() == "Dog");

    animal_sound(animal_dog_ptr);
    animal_sound(dog_dog_ptr);
    animal_sound(dog);
    animal_sound(dog_copy);
    animal_sound(dog_assigment_copy);

    std::cout << '\n';

    // -------------------------- DELETE POINTERS --------------------------
    std::cout << "Lets delete the base ptr" << '\n';
    delete animal_dog_ptr;
    std::cout << '\n';

    delete dog_dog_ptr;
    std::cout << '\n';

    // -------------------------- MOVE TYPES --------------------------
    std::cout << "move stuff over" << '\n';
    Dog dog_move = std::move(dog);
    std::cout << '\n';

    Dog dog_assigment_move;
    dog_move = std::move(dog_copy);
    std::cout << '\n';

    // -------------------------- USE CLONES --------------------------
    std::cout << "Assert clone and moved objects" << '\n';

    assert(dog.getType() == "");
    assert(dog_copy.getType() == "");
    assert(dog_move.getType() == "Dog");
    assert(dog_assigment_move.getType() == "Dog");

    animal_sound(dog_move);
    animal_sound(dog_assigment_move);

    std::cout << '\n';
}
