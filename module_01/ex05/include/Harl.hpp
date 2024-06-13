/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Harl.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/21 03:49:09 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/01/24 15:43:25 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef Harl_h
#define Harl_h

#include <iostream>
#include <map>
#include <string>

class Harl {
public:
  Harl();

  void complain(std::string level);

  ~Harl();

private:
  void debug(void);
  void info(void);
  void warning(void);
  void error(void);

  typedef void (Harl::*MemberFunctionPointer)();
  std::map<std::string, MemberFunctionPointer> functionMap;
};

#endif
