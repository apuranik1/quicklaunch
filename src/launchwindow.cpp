#include "launchwindow.h"

#include "app.h"
#include "appscan.h"
#include "history.h"

#include <cstdlib>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>

using Gtk::Box;
using Gtk::Widget;
using Gtk::Image;
using Gtk::Label;
using std::vector;

namespace quicklaunch
{

    Launcher::Launcher(const App& app) :
        app(app)
    {
        box = new Box(Gtk::ORIENTATION_VERTICAL);
        Gtk::Image* icon = Gtk::manage(new Image());
        icon->set_from_icon_name(app.icon_name(), Gtk::ICON_SIZE_LARGE_TOOLBAR);
        Gtk::Label* name = Gtk::manage(new Label(app.name()));
        box->pack_end(*icon);
        box->pack_end(*name);
    }

    Launcher::~Launcher()
    {
        delete box;
    }

    void Launcher::launch()
    {
        app.launch();
    }

    const Widget* Launcher::contents() const
    {
        return box;
    }

    Launch_window::Launch_window()
    {
        frequency_map history;
        read_history("/home/alok/test_history", history);
        apps = get_all_apps();
        sort_by_frequency(apps, history);
        
        for (vector<App>::size_type i = 0; i < apps.size(); ++i)
        {
        }
    }

    void Launch_window::execute_app()
    {
        int index = options.get_selected_row()->get_index();
        
    }
    
}
