/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/26 23:33:20 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/26 23:33:20 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tester.hpp"

void redirectCoutToFile(const std::string &filename) {
    std::freopen(filename.c_str(), "w", stdout);
}

void restoreCout() {
    std::fclose(stdout);
    std::freopen("/dev/tty", "a", stdout);
}

std::string readFromFile(const std::string &filename) {
    std::ifstream file(filename.c_str());
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    return content;
}
