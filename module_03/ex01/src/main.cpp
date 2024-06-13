/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/05 15:48:21 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/05 15:48:21 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <fstream>
#include <string>

#include "../include/ScavTrap.hpp"

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

// output checken denk dat het niet klopt...
int main(void) {
  std::string tempFilename = "temp_output.txt";
  std::cout << "Create ClapTrap [Kees] check default values\n";
  ClapTrap claptrap("Kees");
  assert(claptrap.getName() == "Kees");
  assert(claptrap.getPoints() == 10);
  assert(claptrap.getEnergy() == 10);
  assert(claptrap.getDamage() == 0);

  std::cout << "\nCreate ScavTrap [Luuk] check default values\n";
  ScavTrap scavtrap("Luuk");
  assert(scavtrap.getName() == "Luuk");
  assert(scavtrap.getPoints() == 100);
  assert(scavtrap.getEnergy() == 50);
  assert(scavtrap.getDamage() == 20);

  std::cout << "\nClapTrap [Kees] attack ScavTrap [Luuk] and check values\n";
  claptrap.attack("Luuk");
  scavtrap.takeDamage(claptrap.getDamage());
  assert(claptrap.getEnergy() == 9);
  assert(scavtrap.getPoints() == 100);

  std::cout << "\nScavTrap [Luuk] attack ClapTrap [Kees] and check values\n";
  scavtrap.attack("Kees");
  claptrap.takeDamage(scavtrap.getDamage());
  assert(claptrap.getPoints() == 0);
  assert(scavtrap.getEnergy() == 49);

  std::cout << "\nCheck that ClapTrap [Kees] can not do anything\n";
  redirectCoutToFile(tempFilename);
  claptrap.attack("Luuk");
  claptrap.beRepaired(100);
  restoreCout();
  std::string output = readFromFile(tempFilename);
  assert(output.empty() == true);
  std::remove(tempFilename.c_str());

  std::cout << "\nUse all the energy that TrapClap [Luuk] have\n";
  redirectCoutToFile(tempFilename);
  for (int i = 0; i < 49; ++i) {
    scavtrap.attack("Kees");
  }
  restoreCout();
  std::remove(tempFilename.c_str());

  std::cout << "\nCheck that TrapClap [Luuk] can not do anything except for "
               "Gate Keeper mode\n";
  redirectCoutToFile(tempFilename);
  scavtrap.attack("Kees");
  scavtrap.beRepaired(100);
  restoreCout();
  output = readFromFile(tempFilename);
  assert(output.empty() == true);
  std::remove(tempFilename.c_str());

  redirectCoutToFile(tempFilename);
  scavtrap.guardGate();
  restoreCout();
  output = readFromFile(tempFilename);
  assert(output.empty() != true);
  std::remove(tempFilename.c_str());

  std::cout << "\nCheck copy operator for ScavTrap\n";
  ScavTrap scavTrapC(scavtrap);
  assert(scavTrapC.getPoints() == scavtrap.getPoints());
  assert(scavTrapC.getEnergy() == scavtrap.getEnergy());
  assert(scavTrapC.getDamage() == scavtrap.getDamage());
  assert(scavTrapC.getName() == scavtrap.getName());

  std::cout << "\nCheck copy assignment operator ScavTrap\n";
  ScavTrap scavTrapD;
  assert(scavTrapD.getName() == "default");
  scavTrapD = scavTrapC;
  assert(scavTrapC.getPoints() == scavtrap.getPoints());
  assert(scavTrapC.getEnergy() == scavtrap.getEnergy());
  assert(scavTrapC.getDamage() == scavtrap.getDamage());
  assert(scavTrapC.getName() == scavtrap.getName());

  std::cout << "\nPassed all the tests...\n\n";

  return 0;
}
