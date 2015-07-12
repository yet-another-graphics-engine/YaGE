#include "test.h"

#define P_PROP(type, name, format) fprintf(stderr, #name"="#format", ", msg.type.name)
#define P_NAME(type) \
  case Message::type:\
  fprintf(stderr, #type ": ")

#define P_STOP() \
  fprintf(stderr, "\n"); \
break

void test_window_msg()
{
  Window w;
  w.show();

  Message msg;

  while (yage::window::poll(msg)) {
    fprintf(stderr, "[%x] ", msg.time);

    switch (msg.type) {
      P_NAME(type_nop);
      P_STOP();

      P_NAME(type_kbd);
      P_PROP(kbd, is_press, %d);
      P_PROP(kbd, keyval, %u);
      P_PROP(kbd, keycode, %u);
      P_PROP(kbd, is_modkey, %u);
      P_PROP(kbd, modkey_alt, %u);
      P_PROP(kbd, modkey_ctrl, %u);
      P_PROP(kbd, modkey_shift, %u);
      P_STOP();

      P_NAME(type_mouse);
      P_PROP(mouse, x, %.1lf);
      P_PROP(mouse, y, %.1lf);
      P_PROP(mouse, type, %d);
      P_PROP(mouse, is_left, %u);
      P_PROP(mouse, is_right, %u);
      P_PROP(mouse, is_middle, %u);
      P_PROP(mouse, modkey_alt, %u);
      P_PROP(mouse, modkey_ctrl, %u);
      P_PROP(mouse, modkey_shift, %u);
      P_STOP();

      P_NAME(type_window);
      P_PROP(window, type, %d);
      P_STOP();

      default:
      break;
    }
  }
  fprintf(stderr, "test_message: Bye!\n");
}

