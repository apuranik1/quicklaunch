#ifndef XDG_UTIL_H
#define XDG_UTIL_H

#include <string>
#include <vector>

namespace util
{
    std::vector<std::string> get_data_dirs();
    std::string get_history_file();
}

#endif
