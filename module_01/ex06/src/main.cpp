/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/21 03:49:16 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/01/24 15:44:09 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Harl.hpp"

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Expect 1 arg got: " << argc - 1 << "\n";
    return 1;
  }

  Harl debugger;
  debugger.complain(argv[1]);

  return 0;
}
