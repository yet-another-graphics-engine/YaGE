#ifndef WINDOW_H_YDVLBPKF
#define WINDOW_H_YDVLBPKF
#include <gtk/gtk.h>
#include <cstdint>

namespace yage {
namespace core {

class Window {
	friend gboolean event_on_window(GtkWidget *widget, GdkEvent *evt, Window *window);
private:
	GtkWidget *widget_draw_;

public:
	static void init();
	Window();
	~Window();
	void show();
	bool is_valid();
};

struct Message {
	enum {
		type_kbd = 1,
		type_mouse,
		type_window
	} type;
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

} /* core */
} /* yage */

#endif /* end of include guard: WINDOW_H_YDVLBPKF */
