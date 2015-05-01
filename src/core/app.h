#ifndef APP_H_UFDILK3P
#define APP_H_UFDILK3P
#include <gtk/gtk.h>
#include <map>
#include <utility>
#include "window.h"

namespace yage {
namespace core {

struct Message {
	enum {
		mouse = 1,
		keyboard,
		window,
	} type;

	union {
		struct {

		} mouse;

		struct {

		} keyboard;

		struct {

		} window;
	} data;
};

class Window;

class App {
	friend class Window;

private:
	static std::map<GtkWidget *, Window *> map;
	static void event_handler(GdkEvent *evt, gpointer data);
	static void window_add(GtkWidget *gtk, Window *window);
	static void window_del(GtkWidget *gtk, Window *window);

public:
	App() {
		gtk_init(NULL, NULL);
		gdk_event_handler_set(event_handler, nullptr, nullptr);
	};
};

} /* core */
} /* yage */

#endif /* end of include guard: APP_H_UFDILK3P */

