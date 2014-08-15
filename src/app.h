#ifndef APP_H
#define APP_H

#include <string>
#include <vector>

namespace quicklaunch
{
    struct App {
        App(const std::string& cmd, const std::string& name, const std::string& description, const std::string& icon);
        ~App();
        const std::string command;
        const std::string name;
        const std::string description;
        const std::string icon;
    };

    App app_from_file(std::ifstream& file);

}

#endif
