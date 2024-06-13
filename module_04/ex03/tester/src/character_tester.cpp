/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   character_tester.cpp                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:35:10 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/27 16:38:31 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.hpp"

void character_equip_test(Character &character) {
    for (size_t index = 0; index <= character.size(); ++index) {
        redirectCoutToFile(tmp_output);
        AMateria *materia = nullptr;
        restoreCout();
        std::remove(tmp_output.c_str());

        if (index % 2) {
            redirectCoutToFile(tmp_output);
            materia = new Ice();
            restoreCout();
        } else {
            redirectCoutToFile(tmp_output);
            materia = new Cure();
            restoreCout();
        }
        std::remove(tmp_output.c_str());

        if (character.len() == character.size()) {
            character.equip(materia);
            redirectCoutToFile(tmp_output);
            delete materia;
            restoreCout();
            std::remove(tmp_output.c_str());
        } else {
            character.equip(materia);
        }
    }

    assert(character.len() == character.size());
}

void character_unequip_test(Character &character) {
    size_t cur_len = character.len();
    character.unequip(-1);
    character.unequip(4);
    assert(character.len() == cur_len);

    for (int index = 0; index < 4; ++index) {
        redirectCoutToFile(tmp_output);
        character.unequip(index);
        restoreCout();
        std::remove(tmp_output.c_str());
    }

    assert(character.len() == 0);
}

void character_use_test(Character &charachter) {
    std::string output;

    redirectCoutToFile(tmp_output);
    ICharacter *target = new Character(charachter);
    restoreCout();

    redirectCoutToFile(tmp_output);
    charachter.use(-1, *target);
    restoreCout();
    output = readFromFile(tmp_output);
    assert(output == "");
    std::remove(tmp_output.c_str());

    for (size_t index = 0; index < charachter.size(); ++index) {
        redirectCoutToFile(tmp_output);
        charachter.use(int(index), *target);
        restoreCout();
        output = readFromFile(tmp_output);
        std::remove(tmp_output.c_str());

        if (index < charachter.len()) {
            assert(output != "");
        } else {
            assert(output == "");
        }
    }

    redirectCoutToFile(tmp_output);
    delete target;
    restoreCout();
}

void character_test() {
    // -------------------------- CREATE TYPES --------------------------
    std::cout << "Create Character objects" << '\n';
    Character character = Character();
    std::cout << '\n';

    Character character_named = Character("test");
    std::cout << '\n';

    Character character_copy = character;
    std::cout << '\n';

    Character character_assigment_copy;
    character_assigment_copy = character_named;
    std::cout << '\n';

    // -------------------------- ASSERT DEFAULTS --------------------------
    std::cout << "Asssert default values" << '\n';
    assert(character.getName() == "Default");
    assert(character_named.getName() == "test");
    assert(character_copy.getName() == "Default");
    assert(character_assigment_copy.getName() == "test");

    assert(character.len() == 0);
    assert(character_named.len() == 0);
    assert(character_copy.len() == 0);
    assert(character_assigment_copy.len() == 0);
    std::cout << '\n';

    // -------------------------- TEST METHODS --------------------------
    std::cout << "Add equip charachter" << '\n';
    character_equip_test(character);
    character_equip_test(character_named);
    character_equip_test(character_copy);
    character_equip_test(character_assigment_copy);

    std::cout << "Use Charachter" << '\n';
    character_use_test(character);
    character_use_test(character_named);
    character_use_test(character_copy);
    character_use_test(character_assigment_copy);

    std::cout << "Unequip charachter" << '\n';
    character_unequip_test(character);
    character_unequip_test(character_named);
    character_unequip_test(character_copy);
    character_unequip_test(character_assigment_copy);

    std::cout << "Use Charachter" << '\n';
    character_use_test(character);
    character_use_test(character_named);
    character_use_test(character_copy);
    character_use_test(character_assigment_copy);

    std::cout << '\n';

    // -------------------------- MOVE TYPES --------------------------
    std::cout << "move stuff over" << '\n';
    character_equip_test(character);
    Character character_move = std::move(character);
    std::cout << '\n';

    Character character_assigment_move;
    character_assigment_move = std::move(character_copy);
    std::cout << '\n';

    // -------------------------- ASSERT TYPES--------------------------
    std::cout << "Assert clone and moved objects" << '\n';
    assert(character.getName() == "");
    assert(character_copy.getName() == "");

    assert(character_move.getName() == "Default");
    assert(character_assigment_move.getName() == "Default");
    assert(character_move.len() == character_move.size());
    assert(character_assigment_move.len() == 0);

    character_equip_test(character_move);
    character_equip_test(character_assigment_move);

    character_use_test(character_move);
    character_use_test(character_assigment_move);

    character_unequip_test(character_move);
    character_unequip_test(character_assigment_move);
    std::cout << '\n';

    // -------------------------- DELETE TYPES--------------------------
    std::cout << "delete all types" << '\n';
}
