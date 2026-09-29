#include <gtkmm.h>
#include "src/ui/ui.hpp"

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create("example.gtkmm");

    return app->make_window_and_run<MainWindow>(argc, argv);
}