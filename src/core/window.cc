#include "window.h"
#include <glib.h>

namespace {
using namespace yage::core;

void window_on_key(Message &msg, const GdkEvent *evt)
{
	msg.type = Message::type_kbd;
	msg.kbd.is_press = evt->key.type == GDK_KEY_PRESS;
	msg.kbd.keyval = evt->key.keyval;
	msg.kbd.keycode = evt->key.hardware_keycode;

	msg.kbd.is_modkey = evt->key.is_modifier;
	msg.kbd.modkey_shift = evt->key.state & GDK_SHIFT_MASK;
	msg.kbd.modkey_ctrl = evt->key.state & GDK_CONTROL_MASK;
	msg.kbd.modkey_alt = evt->key.state & GDK_MOD1_MASK;
}

void window_on_motion(Message &msg, const GdkEvent *evt)
{
	msg.type = Message::type_mouse;
	msg.mouse.x = evt->motion.x;
	msg.mouse.y = evt->motion.y;

	msg.mouse.is_left = evt->motion.state & GDK_BUTTON1_MASK;
	msg.mouse.is_right = evt->motion.state & GDK_BUTTON3_MASK;
	msg.mouse.is_middle = evt->motion.state & GDK_BUTTON2_MASK;

	msg.mouse.modkey_shift = evt->motion.state & GDK_SHIFT_MASK;
	msg.mouse.modkey_ctrl = evt->motion.state & GDK_CONTROL_MASK;
	msg.mouse.modkey_alt = evt->motion.state & GDK_MOD1_MASK;
}


void window_on_button(Message &msg, const GdkEvent *evt)
{
	msg.type = Message::type_mouse;
	msg.mouse.x = evt->button.x;
	msg.mouse.y = evt->button.y;

	msg.mouse.is_left = evt->button.button == 1;
	msg.mouse.is_right = evt->button.button == 3;
	msg.mouse.is_middle = evt->button.button == 2;

	msg.mouse.modkey_shift = evt->button.state & GDK_SHIFT_MASK;
	msg.mouse.modkey_ctrl = evt->button.state & GDK_CONTROL_MASK;
	msg.mouse.modkey_alt = evt->button.state & GDK_MOD1_MASK;
}

gboolean event_on_window(GtkWidget *widget, GdkEvent *evt, Window *window)
{
	Message msg;
	msg.source = window;
	fprintf(stderr, "Gtk %p Win %p\n", evt->any.window, msg.source);
	switch (evt->type) {
		case GDK_KEY_PRESS:
			window_on_key(msg, evt);
			break;

		case GDK_MOTION_NOTIFY:
			window_on_motion(msg, evt);
			break;

		case GDK_BUTTON_RELEASE:
			msg.mouse.is_press = false;
			window_on_button(msg, evt);
			break;

		case GDK_BUTTON_PRESS:
			msg.mouse.is_press = true;
			window_on_button(msg, evt);
			break;

		case GDK_ENTER_NOTIFY:
			msg.type = Message::type_window;
			msg.window.type = msg.window.type_enter;
			break;

		case GDK_LEAVE_NOTIFY:
			msg.type = Message::type_window;
			msg.window.type = msg.window.type_leave;
			break;

		case GDK_DESTROY:
			msg.type = Message::type_window;
			msg.window.type = msg.window.type_destroy;
			break;

		default:
			fprintf(stderr, "Evt %d\n", evt->type);
			break;
	}
	return false;
}

gpointer event_thread(gpointer data)
{
	gtk_main();
	return nullptr;
}

} /* empty namespace */

namespace yage {
namespace core {

void Window::init()
{
	gtk_init(NULL, NULL);

	// GTK won't fully initialize until now, running a new thread to
	// handle event result in crash.
	//
	// Create a new window to fully initialize GTK.
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_show(window);
	gtk_main_iteration();
	gtk_widget_destroy(window);
	g_thread_new("YaGE GTK event handler", event_thread, nullptr);
}

Window::Window()
{
	GtkWidget *widget_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_events(widget_window, gtk_widget_get_events(widget_window)
			| GDK_BUTTON_PRESS_MASK
			| GDK_POINTER_MOTION_MASK);

	g_signal_connect(widget_window, "event", G_CALLBACK(event_on_window), this);

	widget_draw_ = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER(widget_window), widget_draw_);
}

Window::~Window()
{
}

void Window::show()
{
	gtk_widget_show_all(gtk_widget_get_toplevel(widget_draw_));
}

bool Window::is_valid()
{
	return true;
}

} /* core */
} /* yage */

