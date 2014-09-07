#include "xdgutils.h"

#include <string>
#include <glibmm/miscutils.h>

using std::string;

namespace util
{

    string get_data_dirs()
    {
        bool found;
        static const string XDG_DATA_DIRS = Glib::getenv("XDG_DATA_DIRS", found);
        return found ? XDG_DATA_DIRS : "/usr/local/share/:/usr/share/";
    }

    string get_data_home()
    {
        bool found = false;
        static const string XDG_DATA_HOME = Glib::getenv("XDG_DATA_HOME", found);
        return found ? XDG_DATA_HOME : Glib::getenv("HOME") + "/.local/share/";
        // if HOME is not set, we're gonna have a problem
    }

    string get_history_file()
    {
        return get_data_home() + "quicklaunch_history";
    }
}
