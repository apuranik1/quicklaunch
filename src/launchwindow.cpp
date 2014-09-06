#include "launchwindow.h"

#include "app.h"
#include "appfinder.h"
#include "appscan.h"
#include "history.h"
#include "launcher.h"

#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <memory>
#include <string>
#include <vector>

//#include <iostream>

using Gtk::Box;
using Gtk::Widget;
using std::string;
using std::unique_ptr;
using std::vector;

namespace quicklaunch
{

    // go through range defined by begin and end and look for matches to query
    // just works on iterators returning smart pointers, but wtf, I wanted to try templates
    template<typename iter>
    vector<Launcher*> get_matching_launchers(iter begin, iter end, string query)
    {
        vector<Launcher*> result;
        while (begin != end)
        {
            if ((*begin)->matches(query))
                result.push_back(begin->get());
            ++begin;
        }
        return result;
    }

    Launch_window::Launch_window() :
        container(Gtk::ORIENTATION_VERTICAL)
    {
        frequency_map history;
        // this will be factored out to some other method eventually
        // if this fails...do nothing, actually
        read_history("/home/alok/test_history", history);
        vector<App> apps = get_all_apps();
        sort_by_frequency(apps, history);

        // create vector of launchers
        launchers.reserve(apps.size());
        for (vector<Launcher*>::size_type i = 0; i < apps.size(); ++i)
            launchers.push_back( unique_ptr<Launcher>(new Launcher(apps[i])) );

        add(container);
        container.add(query_entry);
        query_entry.set_text("abiword");

        Gtk::ScrolledWindow* scroll_pane = Gtk::manage(new Gtk::ScrolledWindow());
        scroll_pane->add(options);
        container.add(*scroll_pane);


        query_entry.signal_changed().connect(sigc::mem_fun(*this, &Launch_window::modified_query));
        options.signal_row_activated().connect(sigc::mem_fun(*this, &Launch_window::row_activated));
        show_all_children();
    }

    Launch_window::~Launch_window()
    {
        //std::cout << "Launch_window destructing" << '\n';
    }

    void Launch_window::modified_query()
    {
        //std::cout << "modified" << std::endl;
        string query = query_entry.get_text();
        displayed_launchers = get_matching_launchers(launchers.cbegin(), launchers.cend(), query);

        // clear list of apps
        vector<Widget*> children = options.get_children();
        for (vector<Widget*>::size_type i = 0; i < children.size(); ++i)
        {
            Gtk::Bin* row = static_cast<Gtk::Bin*>(children[i]);
            row->remove();
            options.remove(*row);
            // apparently this works?
            //delete children[i]; // extreme measures
        }

        // rebuild based on new query
        for (vector<Launcher*>::size_type i = 0; i < displayed_launchers.size(); ++i)
        {
            Widget* widget = displayed_launchers[i]->contents();
            //Gtk::ListBoxRow* row = Gtk::manage(new Gtk::ListBoxRow());
            //row->add(*displayed_launchers[i]->contents());
            //widget->show_all();
            options.add(*widget);
        }

        show_all_children();
    }

    void Launch_window::execute_app()
    {
        int index = options.get_selected_row()->get_index();
        displayed_launchers[index]->launch();
        close();
    }

    void Launch_window::row_activated(Gtk::ListBoxRow* row)
    {
        execute_app();
    }
    
}
