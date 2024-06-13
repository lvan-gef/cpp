/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:35:05 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:35:05 by lvan-gef      ########   odam.nl         */
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

#include "../../include/AMateria.hpp"
#include "../../include/Character.hpp"
#include "../../include/Cure.hpp"
#include "../../include/ICharacter.hpp"
#include "../../include/Ice.hpp"
#include "../../include/MateriaSource.hpp"

const std::string tmp_output = "_tmp_output";

void cure_test();
void ice_test();
void character_test();
void materiasource_test();

void redirectCoutToFile(const std::string &filename);
void restoreCout();
void redirectCerrToFile(const std::string &filename);
void restoreCerr();
std::string readFromFile(const std::string &filename);
void replaceAll(std::string &source, const std::string &from,
                const std::string &to);

#endif
