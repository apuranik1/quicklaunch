#ifndef APP_H
#define APP_H

#include <list>
#include <string>
#include <vector>

// TODO: upgrade App to full class
namespace quicklaunch
{
    class App {
        std::string path;
        std::string cmd;
        std::string n;
        std::string descrip;
        std::string icon;
        std::string cwd;
        
        std::list<std::string> prep() const;

    public:
        App(const std::string& app_id, const std::string& cmd, const std::string& name, const std::string& description, const std::string& icon, const std::string& working_dir = "");
        App(std::ifstream& file, const std::string& app_id);
        ~App();
        bool operator== (const App& other) const {
            return path == other.path;
        }
        std::string& name() { // needs to be visible for lots of reasons
            return n;
        };
        const std::string& name() const {
            return n;
        };
        std::string& app_id() { // visible for simple storage to file, among other things
            return path;
        };
        const std::string& app_id() const {
            return path;
        };
        std::string& icon_name() { // the icon is used strictly externally
            return icon;
        };
        //TODO: consider changing icon_name to return an image instead
        const std::string& icon_name() const {
            return icon;
        };
        bool is_valid() const {
            return !cmd.empty();
        };
        bool matches(const std::string& query) const;
        void launch() const;
    };
}

#endif
