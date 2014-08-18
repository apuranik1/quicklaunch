#include "strutils.h"

#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::locale;
using std::string;
using std::vector;
using std::stringstream;

namespace util
{

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

    // basically copied this from SO

    // functor for case-insensitive equality
    struct my_equal {
        my_equal( const std::locale& loc ) : loc_(loc) {}
        bool operator()(char ch1, char ch2) {
            return std::toupper(ch1, loc_) == std::toupper(ch2, loc_);
        }
    private:
        const std::locale& loc_;
    };

    string::size_type find_ignore_case(const string& str, const string& search, const locale& loc)
    {
        string::const_iterator it = std::search(str.begin(), str.end(), 
                search.begin(), search.end(), my_equal(loc));
        if (it != str.end())
            return it - str.begin();
        else return string::npos; // not found
    }

}
