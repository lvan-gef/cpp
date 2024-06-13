/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Sed.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lvan-gef <lvan-gef@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/22 20:04:51 by lvan-gef      #+#    #+#                 */
/*   Updated: 2024/01/24 15:43:18 by lvan-gef      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Sed.hpp"

mySed::mySed(){};

bool mySed::processData(std::string path, const std::string s1,
                        const std::string s2) {
  std::ifstream ifile;
  if (this->readInfile(ifile, path) != true) {
    return false;
  }

  std::ofstream ofile;
  if (this->writeOutfile(ofile, path) != true) {
    ifile.close();
    return false;
  }

  std::string line;
  while (std::getline(ifile, line)) {
    size_t find_pos = line.find(s1);

    if (find_pos == std::string::npos) {
      ofile << line << std::endl;
      continue;
    }

    size_t start_pos = 0;
    while (find_pos != std::string::npos) {
      ofile << line.substr(start_pos, find_pos) << s2;
      start_pos = find_pos + s1.length();
      line = line.substr(start_pos, line.length());
      find_pos = line.find(s1);
      start_pos = 0;
    }

    if (start_pos < line.length())
      ofile << line.substr(start_pos, line.length());
    ofile << std::endl;
  }

  ifile.close();
  ofile.close();

  return true;
}

bool mySed::readInfile(std::ifstream &fileStream, const std::string &path) {
  fileStream.open(path.c_str());
  if (fileStream.is_open() != true) {
    std::cerr << "Failed to open ifile : '" << path << "'\n";
    return false;
  }

  if (isDir(path) != false) {
    fileStream.close();
    std::cerr << "Path is a dir not a file: '" << path << "'\n";
    return false;
  }

  return true;
}

bool mySed::writeOutfile(std::ofstream &fileStream, const std::string &path) {
  fileStream.open((path + ".replace").c_str());

  if (fileStream.is_open() != true) {
    std::cerr << "Failed to open ofile : '" << path << "'\n";
    return false;
  }

  return true;
}

bool mySed::isDir(const std::string &path) {
  struct stat statbuf;

  if (stat(path.c_str(), &statbuf) != 0) {
    return false;
  }
  return S_ISDIR(statbuf.st_mode);
}

mySed::~mySed(){};
