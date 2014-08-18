#ifndef APP_H
#define APP_H

#include <string>

namespace quicklaunch
{
    struct App {
        App(const std::string& cmd, const std::string& name, const std::string& description, const std::string& icon);
        ~App();
        std::string command;
        std::string name;
        std::string description;
        std::string icon;
    };

    App app_from_file(std::ifstream& file);

}

#endif
