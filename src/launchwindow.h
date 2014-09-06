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

namespace quicklaunch
{

    class Launcher;

    class Launch_window : public Gtk::Window
    {
        Gtk::Box container;
        Gtk::Entry query_entry;
        Gtk::ListBox options;
        // vector of owned Launchers
        std::vector< std::unique_ptr<Launcher> > launchers;
        // pointers to specific elements of previous vector
        std::vector<Launcher*> displayed_launchers;

        void regen_displayed(std::string query);
    public:
        Launch_window();
        ~Launch_window();
        void modified_query();
        void row_activated(Gtk::ListBoxRow* row);
        void execute_app();
    };

}

#endif
