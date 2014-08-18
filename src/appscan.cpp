#include "appscan.h"
#include "app.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
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
                        ifstream in(dirname + '/' + name);

                        if (!in)
                        {
                            std::cerr << "Unable to read file " << dirname + name << '\n';
                            continue;
                        }

                        const App& a = app_from_file(in);
                        in.close();
                        if (a.command.length() > 0)
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

    const string HOME_DIR = getenv("HOME");

    static const string APP_DIRS[] =
    {
        "/usr/share/applications",
        "/usr/local/share/applications",
        HOME_DIR + "/.local/share/applications"
    };
    static const int APP_DIR_COUNT = 3;

    vector<App> get_all_apps()
    {
        vector<App> apps;

        for (int i = 0; i < APP_DIR_COUNT; i++)
            scan_dir(APP_DIRS[i], apps);

        return apps;
    }
}
