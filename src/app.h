#ifndef APP_H
#define APP_H

#include <string>

namespace quicklaunch
{
    struct App {
        App(const std::string& id, const std::string& cmd, const std::string& name, const std::string& description, const std::string& icon);
        ~App();
        std::string id;
        std::string command;
        std::string name;
        std::string description;
        std::string icon;
    };

    /* 
     * Generate an app from a desktop entry. Returns an app with all fields
     * blank if the file is not a desktop entry or the app is explicitly hidden.
     * app_id can usually be the path to the file.
     */
    App app_from_file(std::ifstream& file, const std::string& app_id);

}

#endif
