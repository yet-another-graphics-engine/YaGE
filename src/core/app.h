#ifndef APP_H_UFDILK3P
#define APP_H_UFDILK3P
#include <gtk/gtk.h>
#include <map>
#include <utility>
#include <cstdint>
#include "window.h"

namespace yage {
namespace core {
class Window;

struct Message {
	enum {
		type_kbd = 1,
		type_mouse,
		type_window
	} type;

	uint32_t time;
	Window *source;

	union {
		struct {
			bool is_press;
			uint32_t keyval;
			uint16_t keycode;

			bool is_modkey		: 1;
			bool modkey_alt 	: 1;
			bool modkey_ctrl 	: 1;
			bool modkey_shift	: 1;
		} kbd;

		struct {
			double x, y;

			bool is_press 		: 1;
			bool is_left 		: 1;
			bool is_right 		: 1;
			bool is_middle 		: 1;

			bool modkey_alt 	: 1;
			bool modkey_ctrl 	: 1;
			bool modkey_shift	: 1;
		} mouse;

		struct {
			enum {
				type_enter = 1,
				type_leave,
				type_destroy
			} type;
		} window;
	};
};

class App {
	friend class Window;

private:
	static std::map<GtkWidget *, Window *> map;
	static void event_handler(GdkEvent *evt, gpointer data);
	static void window_add(GtkWidget *gtk, Window *window);
	static void window_del(GtkWidget *gtk);
	static Window *window_lookup(GtkWidget *gtk);

public:
	App() {
		gtk_init(NULL, NULL);
		gdk_event_handler_set(event_handler, nullptr, nullptr);
	};
};

} /* core */
} /* yage */

#endif /* end of include guard: APP_H_UFDILK3P */

