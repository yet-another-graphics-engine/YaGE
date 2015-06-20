#include "message.h"
#include "../draw/canvas.h"
#ifdef _MSC_VER
#pragma warning(disable:4800)
#endif
#include "../yage.h"

namespace yage {
namespace window {

using yage::draw::Canvas;
using yage::draw::Point;

void Window::msg_push_queue(Message &msg)
{
  g_async_queue_push(Window::msg_queue_, &msg);
}

void Window::msg_window_on_destroy(GtkWidget *widget, Window *source)
{
  source->gtk_draw_ = nullptr;
  source->gtk_window_ = nullptr;
  --Window::window_num_;

  if (source->cairo_surface_ != nullptr) {
    cairo_surface_destroy(source->cairo_surface_);
    source->cairo_surface_= nullptr;
  }

  if(Window::quit_all_windows_destroyed && Window::window_num_ == 0)
  {
    gtk_main_quit();
    return;
  }

  Message &msg = *(new Message);
  msg.source = source;
  msg.type = msg.type_window;
  msg.window.type = msg.window.type_destroy;
  msg_push_queue(msg);
}

gboolean Window::msg_window_on_focus(GtkWidget *widget, GdkEvent *event, Window *source)
{
  Message &msg = *(new Message);
  msg.source = source;
  msg.type = msg.type_window;

  msg.window.type = event->focus_change.in ?
                    msg.window.type_enter :
                    msg.window.type_leave;
  msg_push_queue(msg);

  if(source->show_flag_ == false)
  {
    GdkWindow* window = gtk_widget_get_window(widget);
    GdkRectangle area;
    gdk_window_get_frame_extents(window, &area);
    source->title_bar_height_ = area.height - gdk_window_get_height(window);
    g_cond_signal(&source->show_cond_);
  }
  return false;
}

gboolean Window::msg_window_on_key(GtkWidget *widget, GdkEvent *event, Window *source)
{
  Message &msg = *(new Message);
  msg.source = source;
  msg.type = msg.type_kbd;

  msg.kbd.is_press = (event->key.type == GDK_KEY_PRESS);
  msg.kbd.keyval = event->key.keyval;
  msg.kbd.keycode = event->key.hardware_keycode;

  msg.kbd.is_modkey = event->key.is_modifier;
  msg.kbd.modkey_shift = event->key.state & GDK_SHIFT_MASK;
  msg.kbd.modkey_ctrl = event->key.state & GDK_CONTROL_MASK;
  msg.kbd.modkey_alt = event->key.state & GDK_MOD1_MASK;

  msg_push_queue(msg);
  return false;
}

// For:
// GDK_MOTION_NOTIFY
// GDK_BUTTON_RELEASE
// GDK_BUTTON_PRESS:
//
// if we let GTK to process the event, there will be
// the same event come immediately.

gboolean Window::msg_draw_on_button(GtkWidget *widget, GdkEvent *event, Window *source)
{
  Message &msg = *(new Message);
  msg.source = source;
  msg.type = msg.type_mouse;
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

  msg_push_queue(msg);
  return true;
}

gboolean Window::msg_draw_on_motion(GtkWidget *widget, GdkEvent *event, Window *source)
{
  Message &msg = *(new Message);
  msg.source = source;
  msg.type = msg.type_mouse;
  msg.mouse.type = msg.mouse.type_move;

  msg.mouse.x = event->motion.x;
  msg.mouse.y = event->motion.y;

  msg.mouse.is_left = event->motion.state & GDK_BUTTON1_MASK;
  msg.mouse.is_right = event->motion.state & GDK_BUTTON3_MASK;
  msg.mouse.is_middle = event->motion.state & GDK_BUTTON2_MASK;

  msg.mouse.modkey_shift = event->motion.state & GDK_SHIFT_MASK;
  msg.mouse.modkey_ctrl = event->motion.state & GDK_CONTROL_MASK;
  msg.mouse.modkey_alt = event->motion.state & GDK_MOD1_MASK;

  msg_push_queue(msg);
  return true;
}

gboolean Window::msg_draw_on_conf(GtkWidget *widget, GdkEventConfigure *event, Window *source)
{
  Message &msg = *(new Message);
  msg.source = source;
  msg.type = msg.type_window;
  msg.window.type = msg.window.type_resize;
  msg_push_queue(msg);
  //g_print("on_draw_resize\n");
  gtk_window_get_size(source->gtk_window_, &source->window_width_, &source->window_height_);
  if(source->size_change_flag_ == false)
    g_cond_signal(&source->resize_cond_);
  return true;
}

gboolean Window::msg_draw_on_draw(GtkWidget *widget, cairo_t *cairo, Window *source)
{
  cairo_surface_t* surface = source->cairo_surface_;
  if (surface) {
    cairo_set_source_surface(cairo, surface, 0, 0);
    cairo_paint(cairo);
  }
  else {
    cairo_set_source_rgb(cairo,1,1,1);
    cairo_paint(cairo);
  }
  return true;
}

} /* window */
} /* yage */

