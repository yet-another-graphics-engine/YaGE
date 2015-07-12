#ifndef WINDOW_MESSAGE_H_
#define WINDOW_MESSAGE_H_

#ifndef _MSC_VER
#include <stdint.h>
#else
#if _MSC_VER < 1600
#include "../../include/yage/stdint.h"
#else
#include <stdint.h>
#endif
#endif

#include <gtk/gtk.h>
#include "window.h"

namespace yage {
namespace window {

class Window;
class Timer;

struct Message {
  enum {
    type_nop = 0,
    type_kbd,
    type_mouse,
    type_window,
    type_timer
  } type;

  Window *source;
  uint32_t time;

  union {
    struct {
      uint8_t is_press;
      uint32_t keyval;
      uint16_t keycode;

      uint8_t is_modkey    : 1;
      uint8_t modkey_alt   : 1;
      uint8_t modkey_ctrl  : 1;
      uint8_t modkey_shift : 1;
    } kbd;

    struct {
      double x, y;

      enum {
        type_press = 1,
        type_release,
        type_move
      } type;

      uint8_t is_left      : 1;
      uint8_t is_right     : 1;
      uint8_t is_middle    : 1;

      uint8_t modkey_alt   : 1;
      uint8_t modkey_ctrl  : 1;
      uint8_t modkey_shift : 1;
    } mouse;

    struct {
      enum {
        type_enter = 1,
        type_leave,
        type_destroy,
        type_resize
      } type;
    } window;

    struct {
      Timer *timer;

      enum {
        type_running = 1,
        type_finished
      } type;

      double seconds;
    } timer;
  };
};

} /* window */
} /* yage */

#endif /* end of include guard: MESSAGE_H_JDF1VFPO */
