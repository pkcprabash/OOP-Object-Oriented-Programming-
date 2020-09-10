#include "project.h"
#include <gtkmm/application.h>

using namespace std;
int main(int argc, char *argv[])
{
	Gtk:: Main app(argc, argv);
	Login_window w;
	Gtk::Main::run(w);
	return 0;

}

