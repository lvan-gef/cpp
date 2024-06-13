#ifndef Utils_h
#define Utils_h

#include <iostream>
#include <sstream>

bool isValidString(const std::string &str);
bool isValidNumber(const std::string &str);

std::string trim(const std::string &str);
std::string intToString(const int value);
std::string truncateString(const std::string &str, const size_t maxWidth);
std::string rightPad(const std::string &str, const size_t size,
                     const char paddingChar);

int stringToInt(const std::string &str);

#endif
