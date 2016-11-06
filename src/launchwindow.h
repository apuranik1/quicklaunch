#ifndef LAUNCH_WINDOW_H
#define LAUNCH_WINDOW_H

#include "app.h"

#include <gtkmm/window.h>
#include <gtkmm/entry.h>
#include <gtkmm/listbox.h>
#include <gtkmm/box.h>

#include <memory>
#include <string>
#include <vector>

namespace Gtk
{
    class ListBoxRow;
}

namespace liftoff
{

    class Launcher;

    class Launch_window : public Gtk::Window
    {
        Gtk::Box container;
        Gtk::Entry query_entry;
        Gtk::ListBox options;
        // more cpu usage, but hopefully lots less memory
        std::vector<App> apps;
        // vector of owned Launchers
//        std::vector< std::unique_ptr<Launcher> > launchers;
        // displayed launchers
        std::vector<Launcher> displayed_launchers;

        void regen_displayed(const std::string& query);
    public:
        Launch_window();
        ~Launch_window();
        void modified_query();
        void row_activated(Gtk::ListBoxRow* row);
        bool key_press(GdkEventKey* event);
        void execute_app();
    };

}

#endif
