/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Utils.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 23:23:07 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/01/12 04:23:04 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Utils.hpp"

std::string intToString(const int value) {
  std::stringstream str;
  str << value;
  return str.str();
}

int stringToInt(const std::string &str) {
  std::istringstream iss(str);
  int value;
  if (iss >> value) {
    return value;
  }
  return 0;
}

std::string truncateString(const std::string &str, const size_t maxWidth) {
  if (str.length() > maxWidth) {
    return str.substr(0, maxWidth - 1) + ".";
  }
  return str;
}

std::string rightPad(const std::string &str, const size_t size,
                     const char paddingChar) {
  if (str.length() >= size) {
    return str;
  }
  return str + std::string(size - str.length(), paddingChar);
}

std::string trim(const std::string &str) {
  size_t firstChar = str.find_first_not_of(" \t\n\r\f\v");
  if (firstChar == std::string::npos) {
    return "";
  }

  size_t lastChar = str.find_last_not_of(" \t\n\r\f\v");
  return str.substr(firstChar, (lastChar - firstChar + 1));
}

bool isValidString(const std::string &str) {
  for (size_t i = 0; i < str.length(); i++) {
    if (isalpha(static_cast<unsigned char>(str[i])) == 0) {
      return false;
    }
  }
  return true;
}

bool isValidNumber(const std::string &str) {
  for (size_t i = 0; i < str.length(); i++) {
    if (isdigit(static_cast<unsigned char>(str[i])) == 0) {
      return false;
    }
  }
  return true;
}
