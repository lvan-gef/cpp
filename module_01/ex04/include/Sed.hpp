/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Sed.hpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/21 03:48:49 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/06/13 21:25:56 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef Sed_H
#define Sed_H

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <sys/stat.h>

class mySed {
  public:
    mySed();
    bool processData(std::string path, const std::string s1,
                     const std::string s2);
    ~mySed();

  private:
    bool readInfile(std::ifstream &fileStream, const std::string &path);
    bool writeOutfile(std::ofstream &fileStream, const std::string &path);
    bool isDir(const std::string &path);
};
#endif
