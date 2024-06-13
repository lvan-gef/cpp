/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Account.cpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 23:25:48 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/01/12 04:24:12 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Account.hpp"

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

Account::Account(int initial_deposit) {
  Account::_nbDeposits = -1;
  Account::_amount = 0;
  Account::_nbWithdrawals = 0;
  this->makeDeposit(initial_deposit);
}

int Account::getNbAccounts(void) { return _nbAccounts; }

int Account::getTotalAmount(void) { return _totalAmount; }

int Account::getNbDeposits(void) { return _totalNbDeposits; }

int Account::getNbWithdrawals(void) { return _totalNbWithdrawals; }

void Account::displayAccountsInfos() {
  _displayTimestamp();
  std::cout << "accounts:" << getNbAccounts() << ";total:" << getTotalAmount()
            << ";deposits:" << getNbDeposits()
            << ";withdrawals:" << getNbWithdrawals() << std::endl;
  return;
}

void Account::makeDeposit(int deposit) {
  if (deposit < 0) {
    return;
  }

  int prevAmount = this->checkAmount();
  this->_amount += deposit;
  _totalAmount += deposit;

  if (this->_nbDeposits == -1) {
    this->_accountIndex = this->_nbAccounts;
    this->_displayTimestamp();
    std::cout << "index:" << this->_accountIndex
              << ";amount:" << this->checkAmount() << ";created" << std::endl;
    this->_nbAccounts++;
    this->_nbDeposits++;
  } else {
    this->_nbDeposits++;
    this->_displayTimestamp();
    std::cout << "index:" << this->_accountIndex << ";p_amount:" << prevAmount
              << ";deposit:" << deposit << ";amount:" << this->checkAmount()
              << ";nb_deposits:" << this->_nbDeposits << std::endl;
    _totalNbDeposits++;
  }
  return;
}

bool Account::makeWithdrawal(int withdrawal) {
  if (withdrawal > this->_amount) {
    this->_displayTimestamp();
    std::cout << "index:" << this->_accountIndex
              << ";p_amount:" << this->checkAmount() << ";withdrawal:refused"
              << std::endl;
    return false;
  }

  int prevAmount = this->checkAmount();
  this->_amount -= withdrawal;
  _totalAmount -= withdrawal;
  this->_nbWithdrawals++;
  _totalNbWithdrawals++;

  this->_displayTimestamp();
  std::cout << "index:" << this->_accountIndex << ";p_amount:" << prevAmount
            << ";withdrawal:" << withdrawal << ";amount:" << this->checkAmount()
            << ";nb_withdrawals:" << this->_nbWithdrawals << std::endl;

  return true;
}

int Account::checkAmount(void) const { return this->_amount; }

void Account::displayStatus(void) const {
  _displayTimestamp();
  std::cout << "index:" << this->_accountIndex
            << ";amount:" << this->checkAmount()
            << ";deposits:" << this->_nbDeposits
            << ";withdrawals:" << this->_nbWithdrawals << std::endl;
  return;
}

void Account::_displayTimestamp(void) {
  time_t currentTime = time(0);
  const tm *localTime = localtime(&currentTime);
  std::cout << "[" << localTime->tm_year + 1900 << std::setw(2)
            << std::setfill('0') << localTime->tm_mon + 1 << std::setw(2)
            << std::setfill('0') << localTime->tm_mday << "_" << std::setw(2)
            << std::setfill('0') << localTime->tm_hour << std::setw(2)
            << std::setfill('0') << localTime->tm_min << std::setw(2)
            << std::setfill('0') << localTime->tm_sec << "]";
  return;
}

Account::~Account(void) {
  this->_displayTimestamp();
  std::cout << "index:" << this->_accountIndex
            << ";amount:" << this->checkAmount() << ";closed" << std::endl;
  return;
}
