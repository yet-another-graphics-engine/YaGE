#include "test.h"

void test_draw_perf() {
  Window w;
  w.show();
  Canvas canvas(640,480);
  w.set_canvas(&canvas);

  for (int x = 0; x < 640; x += 10) {
      for (int y = 0; y < 480; y += 10) {
          Rect rect;
          rect.first = Point(x - 0.5, y - 0.5);
          rect.second = Point(x + 0.5, y + 0.5);
          canvas.draw_rect(rect);
          w.update_window();
      }
  }

}
