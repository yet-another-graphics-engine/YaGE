#ifndef WINDOW_H_YDVLBPKF
#define WINDOW_H_YDVLBPKF
#include <gtk/gtk.h>
#include "message.h"

namespace yage {
namespace core {

class Window;

struct Message;

class Window {
	friend void yage::core::message_handler::window_on_destroy(GtkWidget *widget, Window *source);
	friend void yage::core::message_handler::push_queue(Message &msg);

private:
	static GAsyncQueue *msg_queue_;
	static size_t window_num_;

	GtkWidget *widget_draw_;

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

} /* core */
} /* yage */

#endif /* end of include guard: WINDOW_H_YDVLBPKF */
