#include "app.h"
#include "strutils.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using std::string;
using std::ifstream;
using util::trim;

namespace quicklaunch
{

    App::App(const string& app_id, const string& cmd, const string& name, const string& description, const string& icon) :
        id(app_id),
        cmd(cmd),
        n(name),
        descrip(description),
        icon(icon)
    {}

    App::App(std::ifstream& file, const string& app_id) :
        id(app_id)
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
            id = "";
            return;
        }
        while (std::getline(file, line))
        {
            line = trim(line);
            string::size_type len = line.length();
            if (len < 5)
                continue;
            if (line.substr(0, 5) == "Name=")
                n = line.substr(5, len);
            else if (line.substr(0, 5) == "Exec=")
                cmd = line.substr(5, len);
            else if (line.substr(0, 5) == "Icon=")
                icon = line.substr(5, len);
            else if (len > 8 && line.substr(0,8) == "Comment=")
                descrip = line.substr(8, len);
            else if (line == "NoDisplay=true")
            {
                id = "";
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

    /*App app_from_file(ifstream& file, const string& id)
    {
        const string ENTRY_ID = "[Desktop Entry]";
        string line;
        string name, cmd, icon, description;
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
            return App("", "", "", "", "");
        while (std::getline(file, line))
        {
            line = trim(line);
            string::size_type len = line.length();
            if (len < 5)
                continue;
            if (line.substr(0, 5) == "Name=")
                name = line.substr(5, len);
            else if (line.substr(0, 5) == "Exec=")
                cmd = line.substr(5, len);
            else if (line.substr(0, 5) == "Icon=")
                icon = line.substr(5, len);
            else if (len > 8 && line.substr(0,8) == "Comment=")
                description = line.substr(8, len);
            else if (line == "NoDisplay=true")
                return App("","","","","");
        }
        return App(app_id, util::trim(cmd), util::trim(name), util::trim(description), util::trim(icon));
    }
    */
}
