#include "gtkmm.h"

#include "Form.h"

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create();
    Form form1(argc, argv);
    return app->run(form1);
}
