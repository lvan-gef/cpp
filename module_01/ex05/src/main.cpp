/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/21 03:49:16 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/01/24 15:43:32 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Harl.hpp"

int main(void) {
  Harl debugger;

  debugger.complain("debug");
  debugger.complain("Debug");
  debugger.complain("dEbug");
  debugger.complain("deBug");
  debugger.complain("debUg");
  debugger.complain("datum");

  debugger.complain("info");
  debugger.complain("Info");
  debugger.complain("iNfo");
  debugger.complain("inFo");
  debugger.complain("infO");
  debugger.complain("information");

  debugger.complain("warning");
  debugger.complain("Warning");
  debugger.complain("wArning");
  debugger.complain("waRning");
  debugger.complain("warNing");
  debugger.complain("Whatever");

  debugger.complain("error");
  debugger.complain("Error");
  debugger.complain("eRror");
  debugger.complain("erRor");
  debugger.complain("errOr");
  debugger.complain("erase");

  debugger.complain("1");
  debugger.complain("#");
  debugger.complain(" ");
  debugger.complain("\n");

  return 0;
}
