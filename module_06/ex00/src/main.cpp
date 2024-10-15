/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 20:23:32 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/15 21:16:41 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ScalarConverter.hpp"

int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cerr << "Expect 1 argument got: " << argc << '\n';
    }

    ScalarConverter::convert(argv[1]);
    return 0;
}
