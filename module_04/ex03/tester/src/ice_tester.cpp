/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ice_tester.cpp                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:35:10 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:35:10 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.hpp"

static void use_test(Ice &ice) {
    redirectCoutToFile(tmp_output);
    ICharacter *target = new Character("testChar");
    restoreCout();
    std::remove(tmp_output.c_str());

    redirectCoutToFile(tmp_output);
    ice.use(*target);
    restoreCout();

    std::string output = readFromFile(tmp_output);
    std::ostringstream eo;
    eo << "Ice: * shoots an ice bolt at " << target->getName() << " *" << '\n';
    std::string expected_output = eo.str();

    assert(output == expected_output);
    std::remove(tmp_output.c_str());
    redirectCoutToFile(tmp_output);
    delete target;
    restoreCout();
    std::remove(tmp_output.c_str());
}

static void use_test(AMateria *ice) {
    redirectCoutToFile(tmp_output);
    ICharacter *target = new Character("testChar");
    restoreCout();
    std::remove(tmp_output.c_str());

    redirectCoutToFile(tmp_output);
    ice->use(*target);
    restoreCout();

    std::string output = readFromFile(tmp_output);
    std::ostringstream eo;
    eo << "Ice: * shoots an ice bolt at " << target->getName() << " *" << '\n';
    std::string expected_output = eo.str();
    assert(output == expected_output);
    std::remove(tmp_output.c_str());

    redirectCoutToFile(tmp_output);
    delete target;
    restoreCout();
    std::remove(tmp_output.c_str());
}

void ice_test() {
    // -------------------------- CREATE TYPES --------------------------
    std::cout << "Create Ice objects" << '\n';
    Ice ice = Ice();
    std::cout << '\n';

    Ice ice_copy = ice;
    std::cout << '\n';

    Ice ice_assigment_copy;
    ice_assigment_copy = ice;
    std::cout << '\n';

    AMateria *ice_clone = ice.clone();
    if (ice_clone == nullptr) {
        std::cerr << "Failed to clone a Ice" << '\n';
        return;
    }
    std::cout << '\n';

    // -------------------------- ASSERT DEFAULTS --------------------------
    std::cout << "Asssert default values" << '\n';
    assert(ice.getType() == "ice");
    assert(ice_copy.getType() == "ice");
    assert(ice_assigment_copy.getType() == "ice");
    assert(ice_clone->getType() == "ice");

    use_test(ice);
    use_test(ice_copy);
    use_test(ice_assigment_copy);
    use_test(ice_clone);

    std::cout << '\n';

    // -------------------------- MOVE TYPES --------------------------
    std::cout << "move stuff over" << '\n';
    Ice ice_move = std::move(ice);
    std::cout << '\n';

    Ice ice_assigment_move;
    ice_assigment_move = std::move(ice_copy);
    std::cout << '\n';

    // -------------------------- ASSERT TYPES--------------------------
    std::cout << "Assert clone and moved objects" << '\n';

    assert(ice.getType() == "");
    assert(ice_copy.getType() == "");
    assert(ice_move.getType() == "ice");
    assert(ice_assigment_move.getType() == "ice");
    std::cout << '\n';

    // -------------------------- DELETE TYPES--------------------------
    delete ice_clone;
}
