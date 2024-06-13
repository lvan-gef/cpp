/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/17 02:07:31 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/01/24 15:42:30 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int main(void) {
  std::string name = "HI THIS IS A BRAIN";
  std::string *namePTR = &name;
  std::string &nameREF = name;

  std::cout << "Mem addr of name   : " << &name << "\n";
  std::cout << "Mem addr of namePTR: " << &namePTR << "\n";
  std::cout << "Mem addr of nameREF: " << &nameREF << "\n";

  std::cout << "Value of name      : " << name << "\n";
  std::cout << "Value of namePTR   : " << *namePTR << "\n";
  std::cout << "Value of nameREF   : " << nameREF << "\n";

  return 0;
}
