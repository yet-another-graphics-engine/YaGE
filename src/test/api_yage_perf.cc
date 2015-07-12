#include "../../include/yage.h"
#include <cmath>
#include <cstdlib>

void test_api_yage_perf(void) {
  yage_init(700, 1300);
  yage_draw_set_auto_update(false);
  struct yage_canvas *bg = yage_canvas_load_image("../src/res/yage-open.svg");
  struct yage_canvas *fg = yage_canvas_load_image("../src/res/yage-error.svg");

  yage_draw_canvas(bg, 0, 0, 20, 20);
  yage_draw_update();
  for (int i = 0; i < 100; ++i) {
    yage_clear();
    yage_draw_canvas(bg, 0, 0, 20, 20);
    yage_draw_canvas(fg, 0, i, 10, 10);
    yage_draw_update_area(0, i - 10, 200, 200);
    yage_sleep(0.01);
  }

  yage_get_key();
}
