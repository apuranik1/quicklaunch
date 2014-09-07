#ifndef XDG_UTIL_H
#define XDG_UTIL_H

#include <string>

namespace util
{
    std::string get_data_home();
    std::string get_data_dirs();
    std::string get_history_file();
}

#endif
