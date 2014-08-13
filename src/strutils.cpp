#include "strutils.h"

#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::stringstream;

vector<string>& split(const string& s, char delim, vector<string>& output)
{
    stringstream stream(s);
    string item;
    while (std::getline(stream, item, delim))
        output.push_back(item);
    return output;
}

vector<string> split(const string& s, char delim)
{
    vector<string> output;
    return split(s, delim, output);
}

string& ltrim(string& s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

string& rtrim(string& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

string& trim(string& s)
{
    return ltrim(rtrim(s));
}
