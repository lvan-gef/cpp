/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/21 03:48:55 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 21:27:10 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Sed.hpp"
#include <cstdlib>

int main(int argc, char *argv[]) {
    if (argc < 4 || argc > 4) {
        std::cerr << "Expect 3 arguments got: " << argc - 1 << "\n";
        return EXIT_FAILURE;
    }

    mySed mysed;

    if (mysed.processData(argv[1], argv[2], argv[3]) != true) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
