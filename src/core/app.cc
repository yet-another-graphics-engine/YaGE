#include "app.h"

namespace yage {
namespace core {

void App::event_handler(GdkEvent *evt, gpointer data)
{
	Message msg;
	switch (evt->type) {
		case GDK_KEY_PRESS:
			msg.type = Message::keyboard;
			fprintf(stderr, "Keyboard %d\n", evt->type);
		default:
			break;
	}
	gtk_main_do_event(evt);
}

void App::window_add(GtkWidget *gtk, Window *window) {
	map.insert(std::pair<GtkWidget *, Window *>(gtk, window));
}

void App::window_del(GtkWidget *gtk, Window *window) {
	auto it = map.find(gtk);
	if (it != map.end()) map.erase(it);
}

std::map<GtkWidget *, Window *> App::map;

} /* core */
} /* yage */
