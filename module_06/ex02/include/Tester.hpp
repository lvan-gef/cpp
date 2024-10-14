/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Tester.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 19:54:32 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/10/14 19:54:32 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_HPP
#define TESTER_HPP

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <sstream>

#include "./Base.hpp"

// New class not handled by identify
class D : public Base {
  public:
    D() = default;
    ~D() = default;
};

// helper function
std::string captureOutput(const std::function<void()> &func);
std::string captureStderr(const std::function<void()> &func);
std::pair<std::string, std::string>
captureOutputAndError(const std::function<void()> &func);

void testGenerator(const std::function<Base *()> &generatorFunc);
void testIdentifyPointer(std::function<void(Base *)> identifyFunc);
void testIdentifyReference(std::function<void(Base &)> identifyFunc);
void testEdgeCases(const std::function<void(Base *)> &identifyFunc,
                   const std::function<void(Base &)> &identifyFuncRef);

#endif // !TESTER_HPP
