#ifndef Phonebook_h
#define Phonebook_h

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

#include "Contact.hpp"
#include "Utils.hpp"

class Phonebook {
public:
  Phonebook(void);

  Contact contacts[8];
  void run(void);

  ~Phonebook(void);

private:
  int _counter;
  int _contactLen;

  void _addContact(void);
  bool _adder(const std::string &str);

  void _searchContacts(void);
  void _printContact(const int index);

  void _prettyPrinter(const std::string &str1, const std::string &str2,
                      const std::string &str3, const std::string &str4);
};
#endif
