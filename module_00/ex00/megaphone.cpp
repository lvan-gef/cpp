/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   megaphone.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 22:33:48 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 21:13:15 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cstring>
#include <iostream>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *\n";
    } else {
        for (int i = 1; i < argc; i++) {
            for (int j = 0; j < (int)strlen(argv[i]); j++) {
                putwchar(toupper(argv[i][j]));
            }
        }
        std::cout << "\n";
    }

    return 0;
}
