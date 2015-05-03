#include "message.h"

namespace yage {
namespace core {
namespace message_handler {

void push_queue(Message &msg)
{
  g_async_queue_push(Window::msg_queue_, &msg);
}

void window_on_destroy(GtkWidget *widget, Window *source)
{
  source->widget_draw_ = nullptr;
  --Window::window_num_;

  Message &msg = *(new Message);
  msg.source = source;
  msg.type = msg.type_window;
  msg.window.type = msg.window.type_destroy;
  push_queue(msg);
}

gboolean window_on_focus(GtkWidget *widget, GdkEvent *event, Window *source)
{
  Message &msg = *(new Message);
  msg.source = source;
  msg.type = Message::type_window;

  msg.window.type = event->focus_change.in ?
                    msg.window.type_enter :
                    msg.window.type_leave;
  push_queue(msg);
  return false;
}

gboolean draw_on_key(GtkWidget *widget, GdkEvent *event, Window *source)
{
  Message &msg = *(new Message);
  msg.source = source;
  msg.type = Message::type_kbd;

  msg.kbd.is_press = (event->key.type == GDK_KEY_PRESS);
  msg.kbd.keyval = event->key.keyval;
  msg.kbd.keycode = event->key.hardware_keycode;

  msg.kbd.is_modkey = event->key.is_modifier;
  msg.kbd.modkey_shift = event->key.state & GDK_SHIFT_MASK;
  msg.kbd.modkey_ctrl = event->key.state & GDK_CONTROL_MASK;
  msg.kbd.modkey_alt = event->key.state & GDK_MOD1_MASK;

  push_queue(msg);
  return false;
}

// For:
// GDK_MOTION_NOTIFY
// GDK_BUTTON_RELEASE
// GDK_BUTTON_PRESS:
//
// if we let GTK to process the event, there will be
// the same event come immediately.

gboolean draw_on_button(GtkWidget *widget, GdkEvent *event, Window *source)
{
  Message &msg = *(new Message);
  msg.source = source;
  msg.type = Message::type_mouse;
  msg.mouse.type = (event->any.type == GDK_BUTTON_PRESS ?
                                      msg.mouse.type_press :
                                      msg.mouse.type_release);

  msg.mouse.x = event->button.x;
  msg.mouse.y = event->button.y;

  msg.mouse.is_left = event->button.button == 1;
  msg.mouse.is_right = event->button.button == 3;
  msg.mouse.is_middle = event->button.button == 2;

  msg.mouse.modkey_shift = event->button.state & GDK_SHIFT_MASK;
  msg.mouse.modkey_ctrl = event->button.state & GDK_CONTROL_MASK;
  msg.mouse.modkey_alt = event->button.state & GDK_MOD1_MASK;

  push_queue(msg);
  return true;
}

gboolean draw_on_motion(GtkWidget *widget, GdkEvent *event, Window *source)
{
  Message &msg = *(new Message);
  msg.source = source;
  msg.type = Message::type_mouse;
  msg.mouse.type = msg.mouse.type_move;

  msg.mouse.x = event->motion.x;
  msg.mouse.y = event->motion.y;

  msg.mouse.is_left = event->motion.state & GDK_BUTTON1_MASK;
  msg.mouse.is_right = event->motion.state & GDK_BUTTON3_MASK;
  msg.mouse.is_middle = event->motion.state & GDK_BUTTON2_MASK;

  msg.mouse.modkey_shift = event->motion.state & GDK_SHIFT_MASK;
  msg.mouse.modkey_ctrl = event->motion.state & GDK_CONTROL_MASK;
  msg.mouse.modkey_alt = event->motion.state & GDK_MOD1_MASK;

  push_queue(msg);
  return true;
}

gboolean draw_on_conf(GtkWidget *widget, GdkEventConfigure *event, Window *source)
{
  if (source->cairo_surface_) cairo_surface_destroy(source->cairo_surface_);
  source->cairo_surface_ = gdk_window_create_similar_surface(
      gtk_widget_get_window(widget),
      CAIRO_CONTENT_COLOR,
      gtk_widget_get_allocated_width(widget),
      gtk_widget_get_allocated_height(widget));
  // XXX clear?
  cairo_t *cr;
  cr = cairo_create(source->cairo_surface_);
  cairo_set_source_rgb (cr, 1, 1, 1);
  cairo_paint (cr);
  cairo_destroy (cr);
  return true;
}

gboolean draw_on_draw(GtkWidget *widget, cairo_t *cairo, Window *source)
{
  cairo_set_source_surface(cairo, source->cairo_surface_, 0, 0);
  cairo_paint(cairo);
  return false;
}

} /* msg_handler */
} /* core */
} /* yage */

