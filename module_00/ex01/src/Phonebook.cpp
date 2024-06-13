/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Phonebook.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 23:23:02 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 21:15:06 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Phonebook.hpp"

Phonebook::Phonebook(void) {
    this->_counter = 0;
    this->_contactLen = sizeof(this->contacts) / sizeof(this->contacts[0]);
    return;
}

void Phonebook::run(void) {
    system("clear");
    while (true) {
        std::string option;

        std::cout << "We have 3 options to choice from:\n\t1. ADD\n\t2. "
                     "SEARCH\n\t3. EXIT\nMake your choice > ";
        std::getline(std::cin, option);
        if (std::cin.fail()) {
            std::cout << "Input failed." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (option == "ADD") {
            this->_addContact();
        } else if (option == "SEARCH") {
            this->_searchContacts();
        } else if (option == "EXIT") {
            break;
        } else {
            system("clear");
            std::cout << "\"" << option << "\" is a invallid choice"
                      << std::endl;
        }
    }
    return;
}

void Phonebook::_addContact(void) {
    system("clear");
    if (this->_counter == this->_contactLen) {
        for (int i = 0; i < this->_contactLen - 1; i++) {
            this->contacts[i] = this->contacts[i + 1];
        }
        this->_counter--;
        this->contacts[this->_counter].clearContact();
    }

    if (_adder("firstname") != true) {
        this->contacts[this->_counter].clearContact();
        return;
    }
    if (_adder("lastname") != true) {
        this->contacts[this->_counter].clearContact();
        return;
    }
    if (_adder("nickname") != true) {
        this->contacts[this->_counter].clearContact();
        return;
    }
    if (_adder("phonenumber") != true) {
        this->contacts[this->_counter].clearContact();
        return;
    }
    if (_adder("secret") != true) {
        this->contacts[this->_counter].clearContact();
        return;
    }
    if (this->_counter < this->_contactLen) {
        this->_counter++;
    }

    system("clear");
    return;
}

bool Phonebook::_adder(const std::string &str) {
    std::string placeholder;
    const int size = 22;

    if (str == "firstname" or str == "lastname") {
        std::cout << rightPad(str + " of person", size, ' ') << " > ";
        std::getline(std::cin, placeholder);
        if (std::cin.fail()) {
            std::cout << "Input failed." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }

        placeholder = trim(placeholder);
        if (placeholder == "") {
            system("clear");
            std::cerr << str << " should have at least one letter" << std::endl;
            return false;
        } else if (isValidString(placeholder) != true) {
            system("clear");
            std::cerr << str << " should have alpha only" << std::endl;
            return false;
        }
        if (str == "firstname") {
            this->contacts[this->_counter].setFirstName(placeholder);
        } else {
            this->contacts[this->_counter].setLastName(placeholder);
        }
    } else if (str == "nickname" or str == "secret") {
        std::cout << rightPad(str + " of person", size, ' ') << " > ";
        std::getline(std::cin, placeholder);
        if (std::cin.fail()) {
            std::cout << "Input failed." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }

        placeholder = trim(placeholder);
        if (placeholder == "") {
            system("clear");
            std::cerr << str << " should have at least one char" << std::endl;
            return false;
        }
        if (str == "nickname") {
            this->contacts[this->_counter].setNickName(placeholder);
        } else {
            this->contacts[this->_counter].setSecret(placeholder);
        }
    } else {
        std::cout << rightPad("phonenumber of person", size, ' ') << " > ";
        std::getline(std::cin, placeholder);
        if (std::cin.fail()) {
            std::cout << "Input failed." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return false;
        }

        placeholder = trim(placeholder);
        if (placeholder == "" or isValidNumber(placeholder) != true or
            placeholder.length() != 10) {
            system("clear");
            std::cerr << "Phonenumber should have 10 numbers" << std::endl;
            return false;
        }
        this->contacts[this->_counter].setPhoneNumber(placeholder);
    }
    return true;
}

void Phonebook::_searchContacts(void) {
    system("clear");
    if (this->_counter == 0) {
        return;
    }

    this->_prettyPrinter("index", "firstname", "lastname", "nickname");
    for (int i = 0; i < this->_counter; i++) {
        this->_prettyPrinter(intToString(i), this->contacts[i].getFirstName(),
                             this->contacts[i].getLastName(),
                             this->contacts[i].getNickName());
    }

    std::string placeholder;
    std::cout << "\nWitch person do you want to see? [" << 0 << "-"
              << this->_counter - 1 << "] > ";
    std::getline(std::cin, placeholder);
    if (std::cin.fail()) {
        std::cout << "Input failed." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    if (isValidNumber(placeholder) != true) {
        system("clear");
        std::cerr << "\"" << placeholder << "\" is not a valid number"
                  << std::endl;
        return;
    }

    int number = stringToInt(placeholder);
    if (number < 0 or number >= this->_counter) {
        system("clear");
        std::cerr << "\"" << placeholder << "\" is out of bound [" << 0 << "-"
                  << this->_counter - 1 << "]" << std::endl;
        return;
    }
    system("clear");
    this->_printContact(number);
}

void Phonebook::_prettyPrinter(const std::string &str1, const std::string &str2,
                               const std::string &str3,
                               const std::string &str4) {
    const int maxWidth = 10;

    std::cout << std::setw(maxWidth) << std::right
              << truncateString(str1, maxWidth) << "|" << std::setw(maxWidth)
              << std::right << truncateString(str2, maxWidth) << "|"
              << std::setw(maxWidth) << std::right
              << truncateString(str3, maxWidth) << "|" << std::setw(maxWidth)
              << std::right << truncateString(str4, maxWidth) << std::endl;
}

void Phonebook::_printContact(int index) {
    std::cout << rightPad("firstname", 11, ' ') << " : "
              << this->contacts[index].getFirstName() << std::endl;
    std::cout << rightPad("lastname", 11, ' ') << " : "
              << this->contacts[index].getLastName() << std::endl;
    std::cout << rightPad("nickname", 11, ' ') << " : "
              << this->contacts[index].getNickName() << std::endl;
    std::cout << rightPad("phonenumber", 11, ' ') << " : "
              << this->contacts[index].getPhoneNumber() << std::endl;
    std::cout << rightPad("secret", 11, ' ') << " : "
              << this->contacts[index].getSecret() << std::endl;
}

Phonebook::~Phonebook(void) { return; }
