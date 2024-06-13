/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   brain_tester.cpp                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:34:40 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:34:40 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.hpp"

void add_ideas_test(Dog &dog) {
    assert(dog.add_idea("") == false);

    for (size_t index = 0; index < dog.capacity(); ++index) {
        assert(dog.add_idea("hoi") == true);
    }

    assert(dog.add_idea("hoi") == false);
    assert(dog.len() == dog.capacity());
}

void remove_ideas_test(Dog &dog) {
    for (size_t index = 0; index < dog.capacity(); ++index) {
        dog.remove_idea(index);
    }
    assert(dog.len() == 0);

    dog.remove_idea(200);
    assert(dog.len() == 0);

    dog.remove_idea(5);
    assert(dog.len() == 0);

    add_ideas_test(dog);
    dog.remove_idea("Doei");
    assert(dog.len() == dog.capacity());

    dog.remove_idea("hoi");
    assert(dog.len() == dog.capacity() - 1);

    for (size_t index = 0; index < dog.capacity(); ++index) {
        dog.remove_idea(index);
    }
    assert(dog.len() == 0);

    for (size_t index = 0; index < dog.capacity(); ++index) {
        dog.remove_idea(index);
    }
    assert(dog.len() == 0);
}

void add_ideas_test(Cat &cat) {
    assert(cat.add_idea("") == false);

    for (size_t index = 0; index < cat.capacity(); ++index) {
        assert(cat.add_idea("hoi") == true);
    }

    assert(cat.add_idea("hoi") == false);
    assert(cat.len() == cat.capacity());
}

void remove_ideas_test(Cat &cat) {
    for (size_t index = 0; index < cat.capacity(); ++index) {
        cat.remove_idea(index);
    }
    assert(cat.len() == 0);

    cat.remove_idea(200);
    assert(cat.len() == 0);

    cat.remove_idea(5);
    assert(cat.len() == 0);

    add_ideas_test(cat);
    cat.remove_idea("Doei");
    assert(cat.len() == cat.capacity());

    cat.remove_idea("hoi");
    assert(cat.len() == cat.capacity() - 1);

    for (size_t index = 0; index < cat.capacity(); ++index) {
        cat.remove_idea(index);
    }
    assert(cat.len() == 0);

    for (size_t index = 0; index < cat.capacity(); ++index) {
        cat.remove_idea(index);
    }
    assert(cat.len() == 0);
}

void add_ideas_test(WrongCat &cat) {
    assert(cat.add_idea("") == false);

    for (size_t index = 0; index < cat.capacity(); ++index) {
        assert(cat.add_idea("hoi") == true);
    }

    assert(cat.add_idea("hoi") == false);
    assert(cat.len() == cat.capacity());
}

void remove_ideas_test(WrongCat &cat) {
    for (size_t index = 0; index < cat.capacity(); ++index) {
        cat.remove_idea(index);
    }
    assert(cat.len() == 0);

    cat.remove_idea(200);
    assert(cat.len() == 0);

    cat.remove_idea(5);
    assert(cat.len() == 0);

    add_ideas_test(cat);
    cat.remove_idea("Doei");
    assert(cat.len() == cat.capacity());

    cat.remove_idea("hoi");
    assert(cat.len() == cat.capacity() - 1);

    for (size_t index = 0; index < cat.capacity(); ++index) {
        cat.remove_idea(index);
    }
    assert(cat.len() == 0);

    for (size_t index = 0; index < cat.capacity(); ++index) {
        cat.remove_idea(index);
    }
    assert(cat.len() == 0);
}

void add_ideas_test(Brain &brain) {
    assert(brain.add_idea("") == false);

    for (size_t index = 0; index < brain.capacity(); ++index) {
        assert(brain.add_idea("hoi") == true);
    }

    assert(brain.add_idea("hoi") == false);
    assert(brain.len() == brain.capacity());
}

void remove_ideas_test(Brain &brain) {
    for (size_t index = 0; index < brain.capacity(); ++index) {
        brain.remove_idea(index);
    }
    assert(brain.len() == 0);

    brain.remove_idea(200);
    assert(brain.len() == 0);

    brain.remove_idea(5);
    assert(brain.len() == 0);

    add_ideas_test(brain);
    brain.remove_idea("Doei");
    assert(brain.len() == brain.capacity());

    brain.remove_idea("hoi");
    assert(brain.len() == brain.capacity() - 1);

    for (size_t index = 0; index < brain.capacity(); ++index) {
        brain.remove_idea(index);
    }
    assert(brain.len() == 0);

    for (size_t index = 0; index < brain.capacity(); ++index) {
        brain.remove_idea(index);
    }
    assert(brain.len() == 0);
}

void print_idea_test(Brain &brain) {
    const std::string filename = "_tmp_file";
    std::string output;

    remove_ideas_test(brain);

    redirectCoutToFile(filename);
    brain.print_idea(5);
    restoreCout();
    output = readFromFile(filename);
    assert(output == "");

    redirectCoutToFile(filename);
    brain.print_idea(100);
    restoreCout();
    output = readFromFile(filename);
    assert(output == "");

    add_ideas_test(brain);
    redirectCoutToFile(filename);
    brain.print_idea(5);
    restoreCout();
    output = readFromFile(filename);
    assert(output == "hoi\n");

    redirectCoutToFile(filename);
    brain.print_idea(100);
    restoreCout();
    output = readFromFile(filename);
    assert(output == "");

    redirectCoutToFile(filename);
    brain.print_ideas();
    restoreCout();

    output = readFromFile(filename);
    std::string line;
    size_t counter = 0;
    std::istringstream stream(output);
    while (std::getline(stream, line)) {
        counter++;
    }
    assert(counter == brain.capacity());
    remove_ideas_test(brain);
}

void brain_class_test() {
    // -------------------------- CREATE TYPES --------------------------
    std::cout << "Create Brain objects" << '\n';

    Brain brain = Brain();
    std::cout << '\n';

    Brain brain_copy = brain;
    std::cout << '\n';

    Brain brain_assigment_copy;
    brain_assigment_copy = brain;
    std::cout << '\n';

    // -------------------------- ASSERT DEFAULTS --------------------------
    std::cout << "Asssert default values" << '\n';

    assert(brain.capacity() == 100);
    assert(brain.len() == 0);
    assert(brain_copy.capacity() == 100);
    assert(brain_copy.len() == 0);
    assert(brain_assigment_copy.capacity() == 100);
    assert(brain_assigment_copy.len() == 0);
    std::cout << '\n';

    // -------------------------- USE BRAIN --------------------------
    add_ideas_test(brain);
    add_ideas_test(brain_copy);
    add_ideas_test(brain_assigment_copy);

    remove_ideas_test(brain);
    remove_ideas_test(brain_copy);
    remove_ideas_test(brain_assigment_copy);

    print_idea_test(brain);
    print_idea_test(brain_copy);
    print_idea_test(brain_assigment_copy);

    // -------------------------- MOVE TYPES --------------------------
    add_ideas_test(brain);
    add_ideas_test(brain_copy);
    std::cout << "move stuff over" << '\n';
    Brain brain_move = std::move(brain);
    std::cout << '\n';
    Brain brain_assigment_move;
    brain_assigment_move = std::move(brain_copy);
    std::cout << '\n';

    // -------------------------- ASSERT VALUES --------------------------
    std::cout << "Assert moved objects" << '\n';
    assert(brain_move.len() == brain_move.capacity());
    assert(brain_assigment_move.len() == brain_assigment_move.capacity());

    remove_ideas_test(brain_move);
    remove_ideas_test(brain_assigment_move);

    add_ideas_test(brain_move);
    add_ideas_test(brain_assigment_move);
    std::cout << '\n';
}
