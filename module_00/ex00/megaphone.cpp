/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   megaphone.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 22:33:48 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/01/12 04:22:34 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cstring>
#include <iostream>

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *\n";
  } else {
    for (int i = 1; i < argc; i++) {
      for (int j = 0; j < strlen(argv[i]); j++) {
        putchar(toupper(argv[i][j]));
      }
    }
    std::cout << "\n";
  }

  return 0;
}
