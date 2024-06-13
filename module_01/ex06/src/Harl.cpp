/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Harl.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/21 03:49:16 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/01/24 15:44:09 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Harl.hpp"

Harl::Harl() {
  functionMap["DEBUG"] = &Harl::debug;
  functionMap["INFO"] = &Harl::info;
  functionMap["WARNING"] = &Harl::warning;
  functionMap["ERROR"] = &Harl::error;
  functionMap["SWITCH"] = &Harl::silent;
};

void Harl::complain(std::string level) {
  static std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR", "SWITCH"};
  const std::ptrdiff_t logLevel =
      std::find(levels, levels + 5, std::string(level)) - levels;
  switch (logLevel) {
  case 5:
    std::cerr << "[ Probably complaining about insignificant problems ]\n";
  default:
    for (int i = logLevel; i < 5; i++) {
      MemberFunctionPointer func = functionMap[levels[i]];
      (this->*func)();
    }
  }
};

void Harl::debug(void) {
  std::cout << "[ DEBUG ]\nI love having extra bacon for my "
               "7XL-double-cheese-triple-pickle-specialketchup burger.\nI "
               "really do!\n\n";
};

void Harl::info(void) {
  std::cout
      << "[ INFO ]\nI cannot believe adding extra bacon costs more money. You "
         "didn’t put enough bacon in my burger!\nIf you did, I wouldn’t "
         "be asking for more!\n\n";
};

void Harl::warning(void) {
  std::cout << "[ WARNING ]\nI think I deserve to have some extra bacon for "
               "free.\nI’ve been "
               "coming for years whereas you started working here since last "
               "month.\n\n";
};

void Harl::error(void) {
  std::cout << "[ ERROR ]\nThis is unacceptable, I want to speak to the "
               "manager now.\n\n";
};

void Harl::silent(void) { return; }

Harl::~Harl(){};
