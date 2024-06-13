/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:33:04 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:33:04 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Animal.hpp"
#include "../include/Cat.hpp"
#include "../include/Dog.hpp"
#include "../include/WrongAnimal.hpp"
#include "../include/WrongCat.hpp"

void subject_tester() {
    std::cout << "Create a animal" << '\n';
    const Animal *animal = new (std::nothrow) Animal();
    if (animal == nullptr) {
        std::cerr << "Failed to create a Animal" << '\n';
        exit(1);
    }
    std::cout << '\n';

    std::cout << "Create a Animal Cat" << '\n';
    const Animal *a_cat = new (std::nothrow) Cat();
    if (a_cat == nullptr) {
        std::cerr << "Failed to create a Animal Cat" << '\n';
        delete animal;
        exit(1);
    }
    std::cout << '\n';

    std::cout << "Create a Animal Dog" << '\n';
    const Animal *a_dog = new (std::nothrow) Dog();
    if (a_dog == nullptr) {
        delete animal;
        delete a_cat;
        std::cerr << "Failed to create a Animal Dog" << '\n';
        exit(1);
    }
    std::cout << '\n';

    std::cout << "Check the types" << '\n';
    std::cout << "Animal     type: " << animal->getType() << '\n';
    std::cout << "Animal Cat type: " << a_cat->getType() << '\n';
    std::cout << "Animal Dog type: " << a_dog->getType() << '\n';
    std::cout << '\n';

    std::cout << "Lets make some noise" << '\n';
    std::cout << "Animal: ";
    animal->makeSound();
    std::cout << "Cat   : ";
    a_cat->makeSound();
    std::cout << "Dog   : ";
    a_dog->makeSound();
    std::cout << '\n';

    std::cout << "Delete Animal" << '\n';
    delete animal;
    std::cout << '\n';

    std::cout << "Delete Cat" << '\n';
    delete a_cat;
    std::cout << '\n';

    std::cout << "Delete Dog" << '\n';
    delete a_dog;
    std::cout << '\n';

    std::cout << "Did feels wrong..." << '\n';

    std::cout << "Create a WrongAnimal" << '\n';
    const WrongAnimal *wrong_animal = new (std::nothrow) WrongAnimal();
    if (wrong_animal == nullptr) {
        std::cerr << "Ooh we lucky we can not make a WrongAnimal! Are we..."
                  << '\n';
        exit(1);
    }
    std::cout << '\n';

    std::cout << "Create a WrongAnimal WrongCat" << '\n';
    const WrongAnimal *wrong_cat = new (std::nothrow) WrongCat();
    if (wrong_cat == nullptr) {
        std::cerr << "Sadly we can not make a WrongAnimal WrongCat" << '\n';
        exit(1);
    }
    std::cout << '\n';

    std::cout << "Lets make some wrong noise" << '\n';
    std::cout << "WrongAnimal: ";
    wrong_animal->makeSound();
    std::cout << "WrongCat   : ";
    wrong_cat->makeSound();
    std::cout << '\n';

    std::cout << "Delete WrongAnimal" << '\n';
    delete wrong_animal;
    std::cout << '\n';

    std::cout << "Delete WrongCat" << '\n';
    delete wrong_cat;
    std::cout << '\n';
}

int main() {

    subject_tester();

    return 0;
}
