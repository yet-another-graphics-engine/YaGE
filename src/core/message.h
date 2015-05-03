#ifndef MESSAGE_H_JDF1VFPO
#define MESSAGE_H_JDF1VFPO
#include <cstdint>
#include <gtk/gtk.h>
namespace yage {
namespace core {

class Window;

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

      bool is_modkey    : 1;
      bool modkey_alt   : 1;
      bool modkey_ctrl  : 1;
      bool modkey_shift : 1;
    } kbd;

    struct {
      double x, y;

      enum {
        type_press = 1,
        type_release,
        type_move
      } type;
      bool is_left    : 1;
      bool is_right     : 1;
      bool is_middle    : 1;

      bool modkey_alt   : 1;
      bool modkey_ctrl  : 1;
      bool modkey_shift : 1;
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

namespace message_handler {
void push_queue(Message &msg);
void window_on_destroy(GtkWidget *widget, Window *source);
gboolean draw_on_key(GtkWidget *widget, GdkEvent *event, Window *source);
gboolean draw_on_button(GtkWidget *widget, GdkEvent *event, Window *source);
gboolean draw_on_motion(GtkWidget *widget, GdkEvent *event, Window *source);
gboolean window_on_focus(GtkWidget *widget, GdkEvent *event, Window *source);
} /* message_handler */


} /* core */
} /* yage */

#include "window.h"
#endif /* end of include guard: MESSAGE_H_JDF1VFPO */
