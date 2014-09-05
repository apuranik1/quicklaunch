#include "launcher.h"

#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>

#include <algorithm>
#include <memory>

//#include <iostream>

using Gtk::Box;
using Gtk::Widget;
using Gtk::Image;
using Gtk::Label;
using std::string;
using std::vector;

namespace quicklaunch
{
    Launcher::Launcher(const App& app) :
        app(app),
        box(new Box(Gtk::ORIENTATION_VERTICAL))
    {
        Gtk::Image* icon = Gtk::manage(new Image());
        icon->set_from_icon_name(app.icon_name(), Gtk::ICON_SIZE_LARGE_TOOLBAR);
        Gtk::Label* name = Gtk::manage(new Label(app.name()));
        box->pack_end(*icon);
        box->pack_end(*name);
    }

    Launcher::Launcher(const Launcher& other) :
        Launcher(other.app)
    {}

    //Launcher::Launcher(Launcher&& other) :
    //    app(other.app)
    //{
    //    std::swap(box, other.box);;
    //    other.box = NULL;
    //}

    Launcher::~Launcher()
    {
        //std::cout << "Launcher destructing" << '\n';
        //std::cout << "name is " << app.name() << '\n';
    }

    void Launcher::launch() const
    {
        app.launch();
    }

    Widget* Launcher::contents()
    {
        //std::cout << "Name: " << app.name() << '\n';
        //std::cout << "Returning contents" << std::endl;
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
