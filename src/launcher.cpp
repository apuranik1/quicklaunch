#include "launcher.h"

#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>

#include <algorithm>
#include <memory>
#include <iostream>

using Gtk::Box;
using Gtk::Widget;
using Gtk::Image;
using Gtk::Label;
using std::string;
using std::vector;

namespace quicklaunch
{
    Launcher::Launcher(const App& app) :
        a(app),
        box(new Box(Gtk::ORIENTATION_HORIZONTAL))
    {
        Gdk::RGBA awkward_grey;
        awkward_grey.set_alpha(0);
        box->override_background_color(awkward_grey, Gtk::STATE_FLAG_NORMAL);
        //Gtk::Image* icon = Gtk::manage(new Image());
        //icon->set_from_icon_name(app.icon_name(), Gtk::ICON_SIZE_LARGE_TOOLBAR);
        //icon->set_margin_end(20);
        Gtk::Label* name = Gtk::manage(new Label(app.name()));

        name->set_ellipsize(Pango::ELLIPSIZE_END);
        ///box->pack_start(*icon, false, false);
        box->pack_start(*name, false, false);
        box->show_all();
    }

    Launcher::Launcher(const Launcher& other) :
        Launcher(other.a)
    {}

    Launcher::Launcher(Launcher&& other) noexcept :
        a(other.a)
    {
        std::swap(box, other.box);
        other.box = NULL;
    }

    Launcher::~Launcher()
    {
    }

    void Launcher::launch() const
    {
        a.launch();
    }

    Widget* Launcher::contents()
    {
        box->show_all_children();
        return box.get();
    }

//    template<typename iter>
//    vector<Launcher*> get_matching_launchers(iter start, iter end, const string& query)
//    {
//        vector<Launcher*> output;
//        std::remove_copy_if(start, end, back_inserter(output), 
//                [&query](const Launcher* launcher)
//                {
//                    return !launcher->matches(query);
//                });
//        return output;
//    }

//    vector<Launcher*>& trim_by_query(vector<Launcher*>& launcher_vec, const string& query)
//    {
//        // well that was straightforward...
//        launcher_vec.erase(std::remove_if(launcher_vec.begin(), launcher_vec.end(), 
//                [&query](const Launcher* launcher)
//                {
//                    return !launcher->matches(query);
//                }),
//                launcher_vec.end());
//        return launcher_vec;
//    }
}
