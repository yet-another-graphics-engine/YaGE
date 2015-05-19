#include "test.h"

void test_window_count(void)
{
  Window w;
  w.show();
  w.set_title("Window count test");
  char buf[20];
  int n = 0;

  Message msg;
  while (Window::poll(msg)) {
    if (msg.type != msg.type_mouse) continue;
    if (msg.mouse.type != msg.mouse.type_press) continue;
    if (msg.mouse.is_left) {
      Window *new_win = new Window;
      new_win->show();
      #ifndef _MSC_VER
      snprintf(buf, sizeof(buf), "Window %d", ++n);
      #else
      _snprintf_s(buf, _countof(buf), sizeof(buf), "Window %d", ++n);
      #endif
      new_win->set_title(buf);
    }
    if (msg.mouse.is_right) msg.source->destroy();
  }
  fprintf(stderr, "test_window_count: Bye!\n");
}

