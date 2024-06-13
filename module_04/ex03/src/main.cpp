/* ************************************************************************** */
/*                                                                            */
/*   main.cpp                                           :+:    :+:            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Updated: 2024/03/29 21:05:24 by lvan-gef      ########   odam.nl         */
/*   Updated: 2024/03/28 19:17:25 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/AMateria.hpp"
#include "../include/Character.hpp"
#include "../include/Cure.hpp"
#include "../include/ICharacter.hpp"
#include "../include/Ice.hpp"
#include "../include/MateriaSource.hpp"

void subject_tester() {
    MateriaSource *src = new MateriaSource();
    std::cout << '\n';

    Ice *tmp_ice = new Ice();
    src->learnMateria(tmp_ice);
    std::cout << '\n';
    delete tmp_ice;

    Cure *tmp_cure = new Cure();
    src->learnMateria(tmp_cure);
    std::cout << '\n';
    delete tmp_cure;

    ICharacter *me = new Character("me");
    std::cout << '\n';

    AMateria *tmp;
    tmp = src->createMateria("ice");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);

    ICharacter *bob = new Character("bob");
    std::cout << '\n';
    me->use(0, *bob);
    me->use(1, *bob);

    delete bob;
    std::cout << '\n';

    delete me;
    std::cout << '\n';

    delete src;
    std::cout << '\n';
}

int main() {
    subject_tester();

    return 0;
}
