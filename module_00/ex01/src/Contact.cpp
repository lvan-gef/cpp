/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Contact.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 23:23:14 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/01/12 04:23:21 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Contact.hpp"

Contact::Contact(void) { return; }

void Contact::setFirstName(const std::string &firstName) {
  this->_firstName = firstName;
  return;
}

void Contact::setLastName(const std::string &lastName) {
  this->_lastName = lastName;
  return;
}

void Contact::setNickName(const std::string &nickName) {
  this->_nickName = nickName;
  return;
}

void Contact::setPhoneNumber(const std::string &phoneNumber) {
  this->_phoneNumber = phoneNumber;
  return;
}

void Contact::setSecret(const std::string &secret) {
  this->_secret = secret;
  return;
}

void Contact::clearContact(void) {
  this->_firstName.clear();
  this->_lastName.clear();
  this->_lastName.clear();
  this->_nickName.clear();
  this->_phoneNumber.clear();
  this->_secret.clear();
}

std::string Contact::getFirstName(void) { return this->_firstName; }

std::string Contact::getLastName(void) { return this->_lastName; }

std::string Contact::getNickName(void) { return this->_nickName; }

std::string Contact::getPhoneNumber(void) { return this->_phoneNumber; }

std::string Contact::getSecret(void) { return this->_secret; }

Contact::~Contact(void) { return; }
