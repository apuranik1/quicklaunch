#ifndef LAUNCHER_H
#define LAUNCHER_H

#include "app.h"

#include <algorithm>
#include <memory>
#include <string>


// forward declarations for Launcher
namespace Gtk
{
    class Widget;
    class Box;
}

namespace quicklaunch
{
    /* A class to wrap an App and provide a GUI */
    class Launcher
    {
        //void initialize_widgets();
        App app;
        std::unique_ptr<Gtk::Box> box;
    public:
        Launcher& operator= (const Launcher& rhs) = delete;

        Launcher(const App& app);
        Launcher(const Launcher& other);
        //Launcher(Launcher&& other);
        ~Launcher();
        /* 
         * Return a Widget representing the launcher. The widget is destroyed
         * when the launcher is.
         */
        Gtk::Widget* contents();
        void launch() const;
        bool matches(const std::string& query) const {
            return app.matches(query);
        };
    };

//    template<typename iter>
//    std::vector<Launcher*> get_matching_launchers(iter start, iter end, const std::string& query);
//    std::vector<Launcher*>& trim_by_query(std::vector<Launcher*>& launcher_vec, const std::string& query);

}

#endif
