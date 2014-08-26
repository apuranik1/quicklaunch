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
    class Image;
    class Label;
}

namespace quicklaunch
{
    class Launcher
    {
        // not copyable or assignable
        Launcher(const Launcher& other);
        Launcher& operator=(const Launcher& other);
        App app;
        Gtk::Box* box;
        Gtk::Image* icon;
        Gtk::Label* name;
    public:
        Launcher(const App& app);
        ~Launcher();
        /* 
         * Return a Widget representing the launcher. Memory is managed by the launcher.
         */
        Gtk::Widget* create_contents();
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
