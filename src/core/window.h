#ifndef WINDOW_H_YDVLBPKF
#define WINDOW_H_YDVLBPKF
#include <gtk/gtk.h>
#include <cstdint>

namespace yage {
namespace core {

struct Message;

class Window {
private:
	static GAsyncQueue *msg_queue_;
	static size_t window_num_;
	GtkWidget *widget_draw_;

	static gboolean event_on_window(GtkWidget *widget,
			GdkEvent *evt,
			Window *window);
	static void evt_window_destroy(GtkWidget *widget, Window *window);


public:
	static void init();
	static bool poll(Message &msg, bool block = true);

	Window();
	~Window();
	void show();
	void hide();
	void destroy();
	bool is_valid();
};

struct Message {
	enum {
		type_nop = 0,
		type_kbd,
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

			enum {
				type_press = 1,
				type_release,
				type_move
			} type;
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
