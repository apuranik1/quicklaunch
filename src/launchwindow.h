#ifndef LAUNCH_WINDOW_H
#define LAUNCH_WINDOW_H

#include "app.h"

#include <gtkmm/window.h>
#include <gtkmm/entry.h>
#include <gtkmm/listbox.h>

#include <memory>
#include <string>
#include <vector>

namespace quicklaunch
{

    class Launcher;

    class Launch_window : public Gtk::Window
    {
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
        void execute_app();
    };

}

#endif
