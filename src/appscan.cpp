#include "appscan.h"
#include "app.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>
#include <cstring>

using std::string;
using std::vector;
using std::ifstream;

using namespace quicklaunch;

vector<App> scan_dir(const string& dirname)
{
    vector<App> contents;
    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir(dirname.c_str())) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            string name(ent->d_name);
            if (ent->d_type != 'f')
                continue;
            if (name.length() >= 8 && name.substr(8) == ".desktop")
            {
                ifstream in;
                in.open(name);
                const App& a = app_from_file(in);
                in.close();
                if (a.command.length() > 0)
                    contents.push_back(a);
            }
        }
        return contents;
    }
    else
    {
        //throw std::
    }
}
