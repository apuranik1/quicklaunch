#ifndef LAUNCH_WINDOW_H
#define LAUNCH_WINDOW_H

#include "app.h"

#include <gtkmm.h>
#include <list>

namespace quicklaunch
{
    class Launch_window : public Gtk::Window
    {

    public:
        Launch_window();
        ~Launch_window();
        void signal_search();
        void signal_enter_pressed();
    };

}
#endif
