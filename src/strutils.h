#ifndef STRUTILS_H
#define STRUTILS_H

#include <string>
#include <vector>


std::vector<std::string> split(const std::string&, char);
std::vector<std::string>& split(const std::string&, char, std::vector<std::string>&);

std::string& ltrim(std::string& s);
std::string& rtrim(std::string& s);
std::string& trim(std::string& s);

#endif
