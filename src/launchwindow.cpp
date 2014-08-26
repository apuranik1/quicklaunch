#include "launchwindow.h"

#include "app.h"
#include "appscan.h"

#include <cstdlib>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>

using Gtk::Box;
using Gtk::Widget;
using Gtk::Image;
using Gtk::Label;

namespace quicklaunch
{

    Launcher::Launcher(const App& app) :
        app(app)
    {
    }

    void Launcher::launch()
    {
        app.launch();
    }

    Widget* Launcher::create_contents()
    {
        Box *box = new Box(Gtk::ORIENTATION_VERTICAL);
        Image *img = Gtk::manage(new Image());
        img->set_from_icon_name(app.icon_name(), Gtk::ICON_SIZE_LARGE_TOOLBAR);
        Label *label = Gtk::manage(new Label(app.name()));
        box->pack_end(*img);
        box->pack_end(*label);
        return box;
    }

    Launch_window::Launch_window()
    {
        apps = get_all_apps();
        for (int i = 0; i < apps.size(); ++i)
        {

        }
    }
    
}
