#include "appscan.h"
#include "app.h"

#include "strutils.h"

// rather extensive includes, but not much I can do about it...
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <dirent.h>
#include <cstring>

using std::string;
using std::vector;
using std::ifstream;

namespace quicklaunch
{
    int scan_dir(const string& dirname, vector<App>& app_list)
    {
        std::cout << dirname << '\n';
        static const string ENTRY_ENDING = ".desktop";
        static const int ENDING_LEN = 8;
        DIR* dir;
        struct dirent* ent;
        if ((dir = opendir(dirname.c_str())) != NULL)
        {
            while ((ent = readdir(dir)) != NULL)
            {
                string name(ent->d_name);

                if (name == "." || name == "..")
                    continue;

                if (ent->d_type == DT_DIR)
                {
                    scan_dir(dirname + '/' +  name, app_list);
                }
                else if (ent->d_type == DT_REG)
                {
                    const int len = name.length();
                    if (len >= ENDING_LEN && name.substr(len-ENDING_LEN) == ENTRY_ENDING)
                    {
                        string path = dirname + '/' + name;
                        ifstream in(path);
                        if (!in)
                        {
                            std::cerr << "Unable to read file " << dirname + name << '\n';
                            continue;
                        }

                        const App a(in, path);
                        in.close();
                        if (a.is_valid() > 0)
                            app_list.push_back(a);
                        //else
                        //    std::cerr << "Failed to generate app from " << dirname + name << '\n';
                    }
                    //else
                    //{
                    //    std::cout << "Not a desktop entry: " << name << '\n';
                    //}
                }
            }
            return 0;
        }
        else
        {
            return NO_SUCH_DIR;
        }
    }


    /*static const string APP_DIRS[] =
    {
        "/usr/share/applications",
        "/usr/local/share/applications",
        HOME_DIR + "/.local/share/applications"
    };
    static const int APP_DIR_COUNT = 3;
    */

    vector<App> get_all_apps()
    {
        static const string LOCAL_DATA = string(getenv("HOME")) + "/.local/share/";
        static const string DATA_DIRS = getenv("XDG_DATA_DIRS");
        // full XDG compliance :)
        static const string SEARCH_DIRS = LOCAL_DATA + ":" + (DATA_DIRS.empty() ? "/usr/local/share/:/usr/share/" : DATA_DIRS);
        vector<App> apps;

        vector<string> dirs = util::split(SEARCH_DIRS, ':');;
        for (vector<string>::size_type i = 0; i < dirs.size(); ++i)
            scan_dir(dirs[i] + "/applications", apps);

        return apps;
    }
}
