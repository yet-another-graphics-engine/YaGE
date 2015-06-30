#include "test.h"

void test_window_fix_size()
{
  Window w;
  w.show();
  Message msg;

  Window *t = NULL;
  while (Window::poll(msg)) {
    if (msg.type != msg.type_kbd) continue;
    if (!msg.kbd.is_press) continue;

    switch (msg.kbd.keyval) {
      case 'a':
        if (t) delete t;
        t = new Window;
        t->show();
        fprintf(stderr, "show\n");
        break;

      case 'b':
        if (t) delete t;
        t = new Window;
        t->show();
        t->set_size(100, 200);
        fprintf(stderr, "show, set_size\n");
        break;

      case 'c':
        if (t) delete t;
        t = new Window;
        t->set_resizable(true);
        t->set_size(100, 200);
        t->show();
        fprintf(stderr, "set_res, set_size, show\n");
        break;

      case 'd':
        if (t) delete t;
        t = new Window;
        t->set_size(100, 200);
        t->set_resizable(true);
        t->show();
        fprintf(stderr, "set_size, set_res, show\n");
        break;

      case 'e':
        if (t) delete t;
        t = new Window;
        t->set_size(100, 200);
        t->show();
        t->set_resizable(true);
        fprintf(stderr, "set_size, show, set_res\n");
        break;

      case 'f':
        if (t) delete t;
        t = new Window;
        t->set_resizable(true);
        t->show();
        t->set_size(100, 200);
        fprintf(stderr, "set_res, show, set_size\n");
        break;

      case 'g':
        if (t) delete t;
        t = new Window;
        t->show();
        t->set_resizable(true);
        t->set_size(100, 200);
        fprintf(stderr, "show, set_res, set_size\n");
        break;

      case 'h':
        if (t) delete t;
        t = new Window;
        t->show();
        t->set_size(100, 200);
        t->set_resizable(true);
        fprintf(stderr, "show, set_size, set_res\n");
        break;

    }
  }
}

