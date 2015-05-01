#include "app.h"

namespace {
using namespace yage::core;

void event_handler_key_press(Message &msg, const GdkEvent *evt)
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

void event_handler_motion(Message &msg, const GdkEvent *evt)
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
	msg.type = Message::type_mouse;
}


void event_handler_button(Message &msg, const GdkEvent *evt)
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
	msg.type = Message::type_mouse;
}

} /* empty namespace */

namespace yage {
namespace core {

void App::event_handler(GdkEvent *evt, gpointer data)
{
	Message msg;
	msg.source = App::window_lookup(reinterpret_cast<GtkWidget *>
			(evt->any.window));
	msg.time = evt->key.time;
	switch (evt->type) {
		case GDK_KEY_PRESS:
			event_handler_key_press(msg, evt);
			break;

		case GDK_MOTION_NOTIFY:
			event_handler_motion(msg, evt);
			break;

		case GDK_BUTTON_RELEASE:
			msg.mouse.is_press = false;
			event_handler_button(msg, evt);
			break;

		case GDK_BUTTON_PRESS:
			msg.mouse.is_press = true;
			event_handler_button(msg, evt);
			break;

		case GDK_ENTER_NOTIFY:
			msg.type = Message::type_window;
			msg.window.type = msg.window.type_enter;
			fprintf(stderr, "enter\n");
			break;

		case GDK_LEAVE_NOTIFY:
			msg.type = Message::type_window;
			msg.window.type = msg.window.type_leave;
			fprintf(stderr, "leave\n");
			break;

		case GDK_DESTROY:
			msg.type = Message::type_window;
			msg.window.type = msg.window.type_destroy;
			if (msg.source) {
				App::window_del(msg.source->gtk_);
				msg.source->gtk_ = nullptr;
			}
			break;

		default:
			fprintf(stderr, "Evt %d\n", evt->type);
			break;
	}
	gtk_main_do_event(evt);
}

void App::window_add(GtkWidget *gtk, Window *window) {
	map.insert(std::pair<GtkWidget *, Window *>(gtk, window));
}

void App::window_del(GtkWidget *gtk) {
	auto it = map.find(gtk);
	if (it != map.end()) map.erase(it);
}

Window *App::window_lookup(GtkWidget *gtk)
{
	auto it = map.find(gtk);
	if (it != map.end()) return it->second;
	return nullptr;
}

std::map<GtkWidget *, Window *> App::map;

} /* core */
} /* yage */
