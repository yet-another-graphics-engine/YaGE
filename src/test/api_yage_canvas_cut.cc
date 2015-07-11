#include "../../include/yage.h"
#include <cstddef>

void test_api_yage_canvas_cut(void) {
    struct yage_window *window = yage_init(800, 600);
    yage_circle(100, 100, 50);
    struct yage_canvas *global = yage_window_get_canvas(window);
    struct yage_canvas *canvas1 = yage_canvas_from_canvas(global, 50, 50, 150, 150);
    struct yage_canvas *canvas2 = yage_canvas_from_canvas(global, 50, 150, 150, 50);
    struct yage_canvas *canvas3 = yage_canvas_from_canvas(global, 150, 150, 50, 50);
    struct yage_canvas *canvas4 = yage_canvas_from_canvas(global, 150, 50, 50, 150);

    yage_draw_canvas(canvas1, 0, 200, 1, 1);
    yage_draw_canvas(canvas2, 200, 200, 1, 1);
    yage_draw_canvas(canvas3, 400, 200, 1, 1);
    yage_draw_canvas(canvas4, 600, 200, 1, 1);

    yage_get_key();
    yage_quit();
}
