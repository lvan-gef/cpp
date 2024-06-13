/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cure_tester.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:35:10 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:35:10 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.hpp"

static void use_test(Cure &cure) {
    redirectCoutToFile(tmp_output);
    ICharacter *target = new Character("testChar");
    restoreCout();
    std::remove(tmp_output.c_str());

    redirectCoutToFile(tmp_output);
    cure.use(*target);
    restoreCout();

    std::string output = readFromFile(tmp_output);
    std::ostringstream eo;
    eo << "Cure: * heals " << target->getName() << "'s wounds *" << '\n';
    std::string expected_output = eo.str();
    assert(output == expected_output);
    std::remove(tmp_output.c_str());

    redirectCoutToFile(tmp_output);
    delete target;
    restoreCout();
    std::remove(tmp_output.c_str());
}

static void use_test(AMateria *cure) {
    redirectCoutToFile(tmp_output);
    ICharacter *target = new Character("testChar");
    restoreCout();
    std::remove(tmp_output.c_str());

    redirectCoutToFile(tmp_output);
    cure->use(*target);
    restoreCout();

    std::string output = readFromFile(tmp_output);
    std::ostringstream eo;
    eo << "Cure: * heals " << target->getName() << "'s wounds *" << '\n';
    std::string expected_output = eo.str();

    assert(output == expected_output);
    std::remove(tmp_output.c_str());

    redirectCoutToFile(tmp_output);
    delete target;
    restoreCout();
    std::remove(tmp_output.c_str());
}

void cure_test() {
    // -------------------------- CREATE TYPES --------------------------
    std::cout << "Create Cure objects" << '\n';
    Cure cure = Cure();
    std::cout << '\n';

    Cure cure_copy = cure;
    std::cout << '\n';

    Cure cure_assigment_copy;
    cure_assigment_copy = cure;
    std::cout << '\n';

    AMateria *cure_clone = cure.clone();
    if (cure_clone == nullptr) {
        std::cerr << "Failed to clone a Cure" << '\n';
        return;
    }
    std::cout << '\n';

    // -------------------------- ASSERT DEFAULTS --------------------------
    std::cout << "Asssert default values" << '\n';
    assert(cure.getType() == "cure");
    assert(cure_copy.getType() == "cure");
    assert(cure_assigment_copy.getType() == "cure");
    assert(cure_clone->getType() == "cure");

    use_test(cure);
    use_test(cure_copy);
    use_test(cure_assigment_copy);
    use_test(cure_clone);

    std::cout << '\n';

    // -------------------------- MOVE TYPES --------------------------
    std::cout << "move stuff over" << '\n';
    Cure cure_move = std::move(cure);
    std::cout << '\n';

    Cure cure_assigment_move;
    cure_assigment_move = std::move(cure_copy);
    std::cout << '\n';

    // -------------------------- ASSERT TYPES--------------------------
    std::cout << "Assert clone and moved objects" << '\n';

    assert(cure.getType() == "");
    assert(cure_copy.getType() == "");
    assert(cure_move.getType() == "cure");
    assert(cure_assigment_move.getType() == "cure");
    std::cout << '\n';

    // -------------------------- DELETE TYPES--------------------------
    delete cure_clone;
}
