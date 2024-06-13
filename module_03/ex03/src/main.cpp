/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/05 15:48:51 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/03/05 15:48:51 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cassert>
#include <fstream>
#include <ostream>
#include <string>

#include "../include/ClapTrap.hpp"
#include "../include/DiamondTrap.hpp"
#include "../include/FragTrap.hpp"
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

int main(void) {

  std::string tempFilename = "temp_output.txt";

  std::cout << "Create Diamondtrap [Koen] check default values\n";
  DiamondTrap dt("Koen");
  assert(dt.getPoints() == 100);
  assert(dt.getEnergy() == 50);
  assert(dt.getDamage() == 30);

  std::cout << "\nCreate ClapTrap [Kees] check default values\n";
  ClapTrap claptrap("Kees");
  assert(claptrap.getName() == "Kees");
  assert(claptrap.getPoints() == 10);
  assert(claptrap.getEnergy() == 10);
  assert(claptrap.getDamage() == 0);

  std::cout << "\nDiamond [Koen] attack ClapTrap [Kees] and check values\n";
  dt.attack("test");
  dt.whoAmI();

  std::cout << "\nCreate ScavTrap [Luuk] check default values\n";
  ScavTrap scavtrap("Luuk");
  assert(scavtrap.getName() == "Luuk");
  assert(scavtrap.getPoints() == 100);
  assert(scavtrap.getEnergy() == 50);
  assert(scavtrap.getDamage() == 20);

  std::cout << "\nCreate FragTrap [Bart] check default values\n";
  FragTrap fragtrap("Bart");
  assert(fragtrap.getName() == "Bart");
  assert(fragtrap.getPoints() == 100);
  assert(fragtrap.getEnergy() == 100);
  assert(fragtrap.getDamage() == 30);

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

  std::cout << "\nFragTrap [Bart] attack ScavTrap [Luuk] and check values\n";
  fragtrap.attack("Luuk");
  scavtrap.takeDamage(fragtrap.getDamage());
  assert(scavtrap.getPoints() == 70);
  assert(fragtrap.getEnergy() == 99);

  std::cout << "\nCheck that ClapTrap [Kees] can not do anything\n";
  redirectCoutToFile(tempFilename);
  claptrap.attack("B");
  claptrap.beRepaired(100);
  restoreCout();

  std::string output = readFromFile(tempFilename);
  assert(output.empty() == true);
  std::remove(tempFilename.c_str());

  std::cout << "\nUse all the energy that TrapClap [Luuk] have\n";
  redirectCoutToFile(tempFilename);
  for (int i = 0; i < 49; ++i) {
    scavtrap.attack("A");
  }
  restoreCout();
  std::remove(tempFilename.c_str());

  std::cout << "\nCheck that TrapClap [Luuk] can not do anything except for "
               "Gate Keeper mode\n";
  redirectCoutToFile(tempFilename);
  scavtrap.attack("A");
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

  std::cout << "\nCheck copy operator for DiamondTrap\n";
  DiamondTrap diamondC(dt);
  assert(diamondC.getPoints() == dt.getPoints());
  assert(diamondC.getEnergy() == dt.getEnergy());
  assert(diamondC.getDamage() == dt.getDamage());
  assert(diamondC.getName() == dt.getName());

  std::cout << "\nCheck copy assignment operator DiamondTrap\n";
  DiamondTrap diamondD;
  diamondD = diamondC;
  assert(diamondD.getPoints() == diamondC.getPoints());
  assert(diamondD.getEnergy() == diamondC.getEnergy());
  assert(diamondD.getDamage() == diamondC.getDamage());
  assert(diamondD.getName() == diamondC.getName());

  std::cout << "\nPassed all the tests...\n\n";

  return 0;
}
