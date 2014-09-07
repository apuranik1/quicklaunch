#ifndef STRUTILS_H
#define STRUTILS_H

#include <locale>
#include <string>
#include <vector>

namespace util
{

    std::vector<std::string> split(const std::string&, char);
    std::vector<std::string>& split(const std::string&, char, std::vector<std::string>&);

    std::string& ltrim(std::string& s);
    std::string& rtrim(std::string& s);
    std::string& trim(std::string& s);

    std::string::size_type find_ignore_case(const std::string& str, const std::string& search, const std::locale& loc = std::locale());

    std::string& replace_all(std::string& str, const std::string& to_replace, const std::string& replace_with);
}

#endif
