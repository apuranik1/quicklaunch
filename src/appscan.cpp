#include "appscan.h"
#include "app.h"
#include "xdgutils.h"

#include "strutils.h"

// rather extensive includes, but not much I can do about it...
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>

#include <glibmm/miscutils.h>

using std::string;
using std::vector;
using std::ifstream;

namespace liftoff
{
    int scan_dir(const string& dirname, vector<App>& app_list)
    {
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
                else if (ent->d_type == DT_REG || ent->d_type == DT_LNK)
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
            closedir(dir);
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
        vector<App> apps;

        vector<string> dirs = util::get_data_dirs();
        dirs.push_back(Glib::get_user_data_dir());
        for (vector<string>::size_type i = 0; i < dirs.size(); ++i)
            scan_dir(dirs[i] + "/applications", apps);

        return apps;
    }
}
