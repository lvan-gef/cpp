/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dog_tester.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:34:40 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:34:40 by lvan-gef      ########   odam.nl         */
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

static void animal_sound(AAnimal *ani) {
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
    Dog *dog_dog_ptr = new (std::nothrow) Dog();
    if (dog_dog_ptr == nullptr) {
        std::cerr << "Failed to clone a pointer to a dog" << '\n';
        exit(1);
    }
    std::cout << '\n';

    Dog *copy_dog_ptr = new (std::nothrow) Dog();
    if (copy_dog_ptr == nullptr) {
        std::cerr << "Failed to clone a pointer to a dog" << '\n';
        delete dog_dog_ptr;
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
    assert(dog_dog_ptr->getType() == "Dog");
    assert(copy_dog_ptr->getType() == "Dog");
    assert(dog.getType() == "Dog");
    assert(dog_copy.getType() == "Dog");
    assert(dog_assigment_copy.getType() == "Dog");

    animal_sound(dog_dog_ptr);
    animal_sound(copy_dog_ptr);
    animal_sound(dog);
    animal_sound(dog_copy);
    animal_sound(dog_assigment_copy);

    add_ideas_test(*dog_dog_ptr);
    add_ideas_test(*copy_dog_ptr);
    add_ideas_test(dog);
    add_ideas_test(dog_copy);
    add_ideas_test(dog_assigment_copy);

    remove_ideas_test(*dog_dog_ptr);
    remove_ideas_test(*copy_dog_ptr);
    remove_ideas_test(dog);
    remove_ideas_test(dog_copy);
    remove_ideas_test(dog_assigment_copy);
    std::cout << '\n';

    // -------------------------- DELETE POINTERS --------------------------
    std::cout << "Lets delete the base ptr" << '\n';

    add_ideas_test(*dog_dog_ptr);
    assert(copy_dog_ptr->len() == 0);
    delete dog_dog_ptr;
    std::cout << '\n';

    // -------------------------- MOVE TYPES --------------------------
    add_ideas_test(dog);
    add_ideas_test(dog_copy);
    std::cout << "move stuff over" << '\n';
    Dog dog_move = std::move(dog);
    std::cout << '\n';

    Dog dog_assigment_move;
    dog_assigment_move = std::move(dog_copy);
    std::cout << '\n';

    // -------------------------- ASSERT TYPES--------------------------
    std::cout << "Assert clone and moved objects" << '\n';

    assert(dog.getType() == "");
    assert(dog_copy.getType() == "");
    assert(dog_move.getType() == "Dog");
    assert(dog_assigment_move.getType() == "Dog");

    animal_sound(copy_dog_ptr);
    animal_sound(dog_move);
    animal_sound(dog_assigment_move);

    remove_ideas_test(*copy_dog_ptr);
    remove_ideas_test(dog_move);
    remove_ideas_test(dog_assigment_move);

    add_ideas_test(*copy_dog_ptr);
    add_ideas_test(dog_move);
    add_ideas_test(dog_assigment_move);
    std::cout << '\n';

    delete copy_dog_ptr;
}
