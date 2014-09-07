#include "app.h"
#include "strutils.h"

#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <glibmm/spawn.h>

using std::list;
using std::string;
using std::vector;
using std::ifstream;
using util::trim;

namespace quicklaunch
{

    App::App(const string& app_id, const string& cmd, const string& name, const string& description, const string& icon, const string& working_dir) :
        path(app_id),
        cmd(cmd),
        n(name),
        descrip(description),
        icon(icon),
        cwd(working_dir)
    {}

    App::App(std::ifstream& file, const string& app_id) :
        path(app_id)
    {
        const string ENTRY_ID = "[Desktop Entry]";
        string line;
        bool is_desktop_entry = false;
        while (std::getline(file, line))
        {
            line = trim(line);
            if (line.length() == 0 || line[0] == '#')
                continue;
            // first non-comment line must be the entry label
            if (line == ENTRY_ID)
                is_desktop_entry = true;
            break;
        }
        if (!is_desktop_entry)
        {
            path = "";
            return;
        }
        while (std::getline(file, line))
        {
            line = trim(line);
            string::size_type len = line.length();

            // Different section embedded into desktop entry
            if (len != 0 && line[0] == '[')
                break;
            if (len < 5)
                continue;
            if (line.substr(0, 5) == "Name=")
                n = line.substr(5, len);
            else if (line.substr(0, 5) == "Exec=")
                cmd = line.substr(5, len);
            else if (line.substr(0, 5) == "Icon=")
                icon = line.substr(5, len);
            else if (line.substr(0, 5) == "Path=")
                cwd = line.substr(5, len);
            else if (len > 8 && line.substr(0,8) == "Comment=")
                descrip = line.substr(8, len);
            else if (line == "NoDisplay=true")
            {
                path = "";
                n = "";
                cmd = "";
                icon = "";
                return;
            }
        }
    }

    App::~App() {}

    bool App::matches(const string& query) const
    {
        return  (util::find_ignore_case(n, query) != string::npos
                    || util::find_ignore_case(descrip, query) != string::npos
                    || util::find_ignore_case(cmd, query) != string::npos);
    }

    void App::launch() const
    {
        std::cout << cwd << std::endl;
        Glib::spawn_async(cwd, prep(), Glib::SPAWN_SEARCH_PATH);
    };

    string& unescape(string& str)
    {
        const int ESCAPE_LEN = 2;
        string::size_type pos = 0;
        while ((pos = str.find("\\", pos)) != string::npos)
        {
            if (str.size() == pos + 1)
                return str;
            string new_value;
            switch (str[pos + 1])
            {
                case '\\':
                    new_value = "\\";
                    break;
                case 'n':
                    new_value = "\n";
                    break;
                case 'r':
                    new_value = "\r";
                    break;
                case 's':
                    new_value = " ";
                    break;
                case 't':
                    new_value = "\t";
                    break;
            }
            str.replace(pos, ESCAPE_LEN, new_value);
            pos += new_value.length();
        }
        return str;
    }

    list<string> App::prep() const
    {
        vector<string> argv = util::split(cmd, ' ');
        //for (vector<string>::size_type i = 0; i < argv.size(); ++i)
        //    std::cout << argv[i] << std::endl;
//        list<string> arg_list(argv.begin(), argv.end());
        list<string> arg_list;
        string actual_cmd(cmd);
        unescape(actual_cmd);
        util::replace_all(actual_cmd, "%U", "");
        util::replace_all(actual_cmd, "%u", "");
        util::replace_all(actual_cmd, "%F", "");
        util::replace_all(actual_cmd, "%f", "");
        util::replace_all(actual_cmd, "%i", icon.empty() ? "" : "--icon " + icon);
        util::replace_all(actual_cmd, "%c", n); // I'm not good at the whole localization thing
        util::replace_all(actual_cmd, "%k", path);

//        list<string>::iterator iter = arg_list.begin();
//        while (iter != arg_list.end())
//        {
//            std::cout << *iter << std::endl;
//            if (iter->size() < 2 || iter->at(0) != '%')
//            {
//                ++iter;
//                continue;
//            }
//            if (iter->at(1) == 'i')
//            {
//                if (icon.empty())
//                {
//                    iter = arg_list.erase(iter);
//                }
//                else
//                {
//                    arg_list.insert(iter, "--icon");
//                    *iter = icon;
//                    ++iter;
//                }
//            }
//            else
//            {
//                // not really my problem
//                iter = arg_list.erase(iter);
//            }
//        }
        arg_list.push_back("sh");
        arg_list.push_back("-c");
        arg_list.push_back(actual_cmd);
        arg_list.push_back("--");
        return arg_list;
    }
}
