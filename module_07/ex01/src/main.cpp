/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/23 21:43:14 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/23 21:43:14 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/iter.hpp"

void ft_tolower(char &arr) {
    arr = std::tolower(static_cast<unsigned char>(arr));
}

void ft_toupper(char &arr) {
    arr = std::toupper(static_cast<unsigned char>(arr));
}

void simple_test() {
    char a[] = {'A', 'B', 'C'};

    std::cout << "Original:" << "\n\ta[0]: " << a[0] << "\n\ta[1]: " << a[1]
        << "\n\ta[2]: " << a[2] << std::endl
        << std::endl;

    iter(a, 3, ft_tolower);

    std::cout << "Changed:" << "\n\ta[0]: " << a[0] << "\n\ta[1]: " << a[1]
        << "\n\ta[2]: " << a[2] << std::endl
        << std::endl;

    iter(a, 3, ft_toupper);
    std::cout << "Changed:" << "\n\ta[0]: " << a[0] << "\n\ta[1]: " << a[1]
        << "\n\ta[2]: " << a[2] << std::endl
        << std::endl;
}


int main() {
    simple_test();
    
    return 0;
}
