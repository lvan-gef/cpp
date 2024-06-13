/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Harl.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/21 03:49:16 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 21:27:10 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Harl.hpp"

Harl::Harl() {
    functionMap["debug"] = &Harl::debug;
    functionMap["info"] = &Harl::info;
    functionMap["warning"] = &Harl::warning;
    functionMap["error"] = &Harl::error;
};

void Harl::complain(std::string level) {
    std::map<std::string, MemberFunctionPointer>::iterator it =
        functionMap.find(level);

    if (it != functionMap.end()) {
        MemberFunctionPointer func = it->second;
        (this->*func)();
    } else {
        std::cerr << "Not a valid logging level: " << level << "\n";
    }
};

void Harl::debug(void) {
    std::cout << "I love having extra bacon for my "
                 "7XL-double-cheese-triple-pickle-specialketchup burger. I "
                 "really do!\n";
};
void Harl::info(void) {
    std::cout << "I cannot believe adding extra bacon costs more money. You "
                 "didn’t put enough bacon in my burger! If you did, I wouldn’t "
                 "be asking for more!\n";
};
void Harl::warning(void) {
    std::cout
        << "I think I deserve to have some extra bacon for free. I’ve been "
           "coming for years whereas you started working here since last "
           "month.\n";
};
void Harl::error(void) {
    std::cout << "This is unacceptable! I want to speak to the manager now.\n";
};

Harl::~Harl() {};
