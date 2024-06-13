/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/05 15:47:47 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 22:32:17 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <fstream>
#include <string>

#include "../include/ClapTrap.hpp"

// Function to redirect cout to a file
void redirectCoutToFile(const std::string &filename) {
    std::freopen(filename.c_str(), "w", stdout);
}

// Function to restore cout to standard output
void restoreCout() {
    std::fclose(stdout);
    std::freopen("/dev/tty", "a", stdout);
}

// Function to read content from the temporary file
std::string readFromFile(const std::string &filename) {
    std::ifstream file(filename.c_str());
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    return content;
}

int main(void) {
    // Create a ClapTrap instance with a name
    ClapTrap clapTrapA("A");
    ClapTrap clapTrapB("B");

    // Perform an attack
    clapTrapA.attack("B");
    assert(clapTrapB.getPoints() == 10);
    assert(clapTrapA.getEnergy() == 9);

    // Take damage
    clapTrapB.attack("A");
    clapTrapA.takeDamage(5);
    assert(clapTrapA.getPoints() == 5);
    assert(clapTrapB.getEnergy() == 9);

    // Repair itself
    clapTrapA.beRepaired(3);
    assert(clapTrapA.getPoints() == 8);
    assert(clapTrapA.getEnergy() == 8);

    // Test energy depletion
    for (int i = 0; i < 8; ++i) {
        clapTrapA.attack("B");
    }
    assert(clapTrapA.getEnergy() == 0);

    // test A cannot attack or repair
    std::string tempFilename = "temp_output.txt";
    redirectCoutToFile(tempFilename);
    clapTrapA.attack("B");
    clapTrapA.beRepaired(100);
    restoreCout();
    std::string output = readFromFile(tempFilename);
    assert(output.empty() == true);
    std::remove(tempFilename.c_str());

    // Create a copy of ClapTrap A
    ClapTrap clapTrapC(clapTrapA);
    assert(clapTrapC.getName() == "A");
    assert(clapTrapC.getPoints() == 8);
    assert(clapTrapC.getEnergy() == 0);
    assert(clapTrapC.getDamage() == 0);

    // Use the assignment operator
    ClapTrap clapTrapD;
    assert(clapTrapD.getName() == "default");
    clapTrapD = clapTrapB;
    assert(clapTrapD.getName() == "B");
    assert(clapTrapD.getPoints() == 10);
    assert(clapTrapD.getEnergy() == 9);
    assert(clapTrapD.getDamage() == 0);

    // test D if it stops when it get it by -1000
    clapTrapD.takeDamage(-1000);
    assert(clapTrapD.getPoints() == 0);
    redirectCoutToFile(tempFilename);
    clapTrapD.attack("B");
    clapTrapD.beRepaired(100);
    restoreCout();
    output = readFromFile(tempFilename);
    assert(output.empty() == true);
    std::remove(tempFilename.c_str());

    // test that B still the same
    assert(clapTrapB.getName() == "B");
    assert(clapTrapB.getPoints() == 10);
    assert(clapTrapB.getEnergy() == 9);
    assert(clapTrapB.getDamage() == 0);

    return 0;
}
