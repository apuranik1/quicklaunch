#include "xdgutils.h"

#include <string>
#include <glibmm/miscutils.h>

#include <sys/stat.h>
#include <errno.h>

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
        const string quicklaunch_home = get_data_home() + "quicklaunch/";
        if (mkdir(quicklaunch_home.c_str(), 755))
        {
            // handle screwups
            if (errno != EEXIST)
                // always safe
                return "/dev/null";
        }
        return quicklaunch_home + "history";
    }
}
