#ifndef LAUNCH_WINDOW_H
#define LAUNCH_WINDOW_H

#include "app.h"

#include <gtkmm/window.h>
#include <gtkmm/entry.h>
#include <gtkmm/listbox.h>
#include <vector>

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
        Gtk::Box* box;
    public:
        Launcher& operator= (const Launcher& rhs) = delete;
        Launcher(const Launcher& other) = delete;

        Launcher(const App& app);
        ~Launcher();
        /* 
         * Return a Widget representing the launcher. The widget is destroyed
         * when the launcher is.
         */
        const Gtk::Widget* contents() const;
        void launch();
    };

    class Launch_window : public Gtk::Window
    {
        Gtk::Entry query_entry;
        Gtk::ListBox options;
        std::vector<App> apps;

    public:
        Launch_window();
        ~Launch_window();
        void modified_query();
        void execute_app();
    };

}

#endif
