#include "test.h"

void test_resize()
{
  Window w;
  bool resize = false;
  w.show();
  int x = 300, y = 300;

  Message msg;
  while (Window::poll(msg)) {
    if (msg.type != msg.type_kbd) continue;
    if (!msg.kbd.is_press) continue;

    switch (msg.kbd.keyval) {
      case 't':
        resize = !resize;
        w.set_resizable(resize);
        fprintf(stderr, "Allow resize: %d\n", resize);
        break;

      case 'x':
        x -= 100;
        w.set_size(x, y);
        break;

      case 'X':
        x += 100;
        w.set_size(x, y);
        break;

      case 'y':
        y -= 100;
        w.set_size(x, y);
        break;

      case 'Y':
        y += 100;
        w.set_size(x, y);
        break;

      case 'q':
        fprintf(stderr, "x = %d, y = %d, ", x, y);
        w.get_size(x, y);
        fprintf(stderr, "nx = %d, ny = %d\n", x, y);
        break;

      case '!':
        w.hide();
        sleep_sec(1);
        w.show();
    }
  }
}

