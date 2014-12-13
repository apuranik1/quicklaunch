#include "launcher.h"

#include <glibmm/refptr.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>
#include <gtkmm/icontheme.h>
#include <gdkmm/pixbuf.h>

#include <memory>


using Gtk::Box;
using Gtk::Widget;
using Gtk::Image;
using Gtk::Label;
using Glib::RefPtr;
using Gdk::Pixbuf;
using std::string;
using std::vector;

namespace quicklaunch
{
    Image* icon_from_name(const string& icon_name, const Gtk::IconSize& size)
    {
        Image* icon = new Image();
        int width, height;
        Gtk::IconSize::lookup(size, width, height);
        if (icon_name.length() > 0 && icon_name[0] == '/')
        {
            // use absolute path: some image manipulations required
            RefPtr<Pixbuf> buf = Pixbuf::create_from_file(icon_name);
            buf = buf->scale_simple(width, height, Gdk::INTERP_BILINEAR);
            icon->set(buf);
        }
        else
        {
            // this was freaking painful
            try
            {
                Glib::RefPtr<Gtk::IconTheme> theme(Gtk::IconTheme::get_default());
                RefPtr<Pixbuf> buf = theme->load_icon(icon_name, width);
                buf = buf->scale_simple(width, height, Gdk::INTERP_BILINEAR);
                icon->set(buf);
            }
            catch (Glib::Error err)
            {
                // worst case, it just displays a broken image
                icon->set_from_icon_name(icon_name, size);
            }
        }
        return icon;
    }

    Launcher::Launcher(const App& app) :
        a(app),
        box(new Box(Gtk::ORIENTATION_HORIZONTAL))
    {
        Gdk::RGBA awkward_grey;
        awkward_grey.set_grey(0.5, 0.1);
        box->override_background_color(awkward_grey, Gtk::STATE_FLAG_NORMAL);

        Image* icon = Gtk::manage(icon_from_name(app.icon_name(), Gtk::ICON_SIZE_LARGE_TOOLBAR));

        icon->set_margin_end(20);
        Gtk::Label* name = Gtk::manage(new Label(app.name()));

        name->set_ellipsize(Pango::ELLIPSIZE_END);
        box->pack_start(*icon, false, false);
        box->pack_start(*name, false, false);
        box->show_all();
        box->set_tooltip_text(app.comment());
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
