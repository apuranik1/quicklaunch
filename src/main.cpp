//#include <iostream>

#include "app.h"
#include "appscan.h"
#include "appfinder.h"
#include "history.h"
#include "launchwindow.h"
#include "strutils.h"

#include <gtkmm.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>

using namespace liftoff;

int main(int argc, char *argv[])
{
    //    Glib::RefPtr<Gtk::Application> app =
    //        Gtk::Application::create(argc, argv,
    //                "org.gtkmm.examples.base");
    //    Gtk::Window window;
    //    window.set_default_size(200, 200);
    //
    //    return app->run(window);
    //    std::ifstream in;
    //    in.open("/usr/share/applications/abiword.desktop");
    //    if (!in)
    //    {
    //        std::cerr << "Error opening file" << std::endl;
    //        std::exit(1);
    //    }
    //    const App& test = createFromFile(in);
    //    in.close();
    //    std::cout << test.description << std::endl;

    //std::vector<App> apps = get_all_apps();
    //std::cout << apps.size() << std::endl;
    //frequency_map hist;
    //read_history("/home/alok/test_history", hist);
    ////std::cout << trim_by_query(apps, "FIREFOX").size() << std::endl;
    //std::cout << get_matching_apps(apps.cbegin(), apps.cend(), "text").size() << std::endl;
    //sort_by_frequency(apps, hist);
    //std::cout << get_matching_apps(apps.cbegin(), apps.cend(), "text")[0].app_id() << '\n';
    //std::cout << quicklaunch::trim_history("/home/alok/test_history") << '\n';
    
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv);

    liftoff::Launch_window window;
//    Gtk::Window window;
    //window.set_default_size(200, 300);
    return app->run(window);
}
