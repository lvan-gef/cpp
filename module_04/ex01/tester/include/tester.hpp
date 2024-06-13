/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:33:53 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:33:53 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_HPP
#define TESTER_HPP

#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <new>
#include <ostream>
#include <sstream>
#include <string>

#include "../../include/Animal.hpp"
#include "../../include/Brain.hpp"
#include "../../include/Cat.hpp"
#include "../../include/Dog.hpp"
#include "../../include/WrongAnimal.hpp"
#include "../../include/WrongCat.hpp"

const std::string tmp_output = "_tmp_output";

void animal_test();
void cat_test();
void dog_test();
void wronganimal_test();
void wrongcat_test();

void brain_class_test();
void add_ideas_test(Brain &brain);
void remove_ideas_test(Brain &brain);

void add_ideas_test(Cat &cat);
void remove_ideas_test(Cat &cat);

void add_ideas_test(Dog &dog);
void remove_ideas_test(Dog &dog);

void redirectCoutToFile(const std::string &filename);
void restoreCout();
std::string readFromFile(const std::string &filename);

#endif
