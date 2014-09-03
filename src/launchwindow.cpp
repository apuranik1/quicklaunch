#include "launchwindow.h"

#include "app.h"
#include "appfinder.h"
#include "appscan.h"
#include "history.h"
#include "launcher.h"

#include <cstdlib>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>
#include <memory>
#include <string>
#include <vector>

using Gtk::Box;
using Gtk::Widget;
using Gtk::Image;
using Gtk::Label;
using std::string;
using std::unique_ptr;
using std::vector;

namespace quicklaunch
{

    // go through range defined by begin and end and look for matches to query
    // basically just works on smart pointers, but wtf, I wanted to try templates
    template<typename iter>
    vector<Launcher*> get_matching_launchers(iter begin, iter end, string query)
    {
        vector<Launcher*> result;
        while (begin != end)
        {
            if ((*begin)->matches(query))
                result.push_back(begin->get());
        }
        return result;
    }

    Launch_window::Launch_window()
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
    }

    Launch_window::~Launch_window()
    {
    }

    void Launch_window::modified_query()
    {
        string query = query_entry.get_text();
        displayed_launchers = get_matching_launchers(launchers.cbegin(), launchers.cend(), query);

        // clear list of apps
        vector<Widget*> children = options.get_children();
        for (vector<Widget*>::size_type i = 0; i < children.size(); ++i)
            options.remove(*children[i]);

    }

    void Launch_window::execute_app()
    {
        int index = options.get_selected_row()->get_index();
        displayed_launchers[index]->launch();
        close();
    }
    
}
