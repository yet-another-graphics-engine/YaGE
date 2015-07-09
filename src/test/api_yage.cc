#include "../../include/yage.h"
#include <cmath>
#include <cstdlib>

void test_api_yage(void) {
  const double kPi = 3.1415926;
  yage_window *win_default = yage_init(640, 480);
  yage_window *win_create = yage_window_create(640, 280);
  yage_set_background_color(yage_color_from_string("red"));

  yage_circle(          60, 40, 20);
  yage_circle_fill(     160, 40, 20);
  yage_circle_border(   260, 40, 20);

  yage_color color;
  color.r = 1, color.g = 0, color.b = 0, color.a = 1;
  yage_set_border_color(color);

  yage_window_set_default(win_create);
  yage_ellipse(         360, 40, 20, 10);
  yage_ellipse_fill(    460, 40, 20, 10);
  yage_ellipse_border(  560, 40, 20, 10);

  yage_set_border_thickness(4);

  yage_rectangle(       40, 100, 60, 140);
  yage_rectangle_fill(  140, 100, 160, 140);
  yage_rectangle_border(240, 100, 260, 140);

  yage_set_border_thickness(2);
  color.r = 0, color.g = 1, color.b = 0, color.a = 1;
  yage_set_fill_color(color);

  yage_window_set_default(win_default);
  yage_sector(          360, 140, 20, 0 * kPi / 3, 2 * kPi / 3);
  yage_sector_fill(     460, 140, 20, 2 * kPi / 3, 4 * kPi / 3);
  yage_sector_border(   560, 140, 20, 4 * kPi / 3, 6 * kPi / 3);

  yage_arc_border(      60, 240, 20, kPi, 0);
  yage_line_border(     140, 220, 160, 240);
  double points[] = {100, 200, 200, 100, 0, 0};
  yage_poly(sizeof(points) / sizeof(points[0]) / 2, points);

  struct yage_canvas *canvas = yage_canvas_load_image("../src/res/yage-open.svg");
  int height, width;
  yage_canvas_get_size(canvas, &height, &width);
  yage_draw_canvas(canvas, 540, 220, 1, 1);
  yage_draw_canvas(canvas, 540, 220, 0.5, 0.5);
  yage_draw_canvas(canvas, 540, 220, 0.2, 0.2);
  yage_canvas_delete(canvas);

  yage_set_background_color(yage_color_from_string("green"));
  struct yage_player *player = yage_player_load_music("https://kirito.me/ignite.mp3");
  yage_player_play(player);
  int val_int = yage_input_int("yage_input_int", NULL);
  double val_double = yage_input_double("yage_input_double", NULL);
  yage_set_font_color(yage_color_from_string("Cyan"));

  yage_printf(240, 200, "size = %d x %d, int = %d, double = %lf",
              height, width, val_int, val_double);

  yage_dlg_font(NULL);
  yage_dlg_color(NULL, &color);
  yage_set_font_color(color);
  char val_str[64];
  int num_scanned = yage_input_scanf(NULL, "Enter [str][num]", "%s %d", val_str, &val_int);
  yage_set_font("Microsoft YaHei", 10, true, true);
  yage_printf(240, 240, "num_scanned = %d, str = %s, num = %d", num_scanned, val_str, val_int);

  if (yage_dlg_question(NULL, "Save file?",
                        kYageDlgIconQuestion,
                        kYageDlgButtonYesNo) == kYageDlgResultYes) {
    yage_dlg_message(NULL, yage_dlg_file_save(NULL));;
  } else {
    yage_dlg_message(NULL, yage_dlg_file_open(NULL));;
  }
  yage_player_pause(player);
  struct yage_canvas *btest1 = yage_canvas_load_image("../src/res/yage-open.svg");
  struct yage_canvas *btest2 = yage_canvas_load_image("../src/res/yage-save.svg");
  struct yage_canvas *btest3 = yage_canvas_load_image("../src/res/yage-remove.svg");
  struct yage_button *buttontest = yage_button_create_empty();
  yage_button_set_size(buttontest, 100, 100);
  yage_button_set_position(buttontest, 300, 100);
  yage_button_set_image(buttontest, btest1);
  yage_button_set_focused_image(buttontest, btest2);
  yage_button_set_clicked_image(buttontest, btest3);

  struct yage_button *buttontest1;
  buttontest1 = yage_button_create(0, 0, 100, 100, btest1, btest2, btest3);

  yage_button_update(buttontest);
  yage_button_update(buttontest1);
  yage_message msg;
  while (yage_get_message(&msg, 0)) {
    if (buttontest && yage_button_clicked(buttontest, &msg)) {
      yage_button_set_position(buttontest, yage_random_interval(0,540), yage_random_interval(0,380));
      yage_button_update(buttontest);
      yage_button_set_visibility(buttontest1,0);
      yage_button_update(buttontest1);

    }
    if (buttontest1 && yage_button_clicked(buttontest1, &msg)){
      yage_button_set_size(buttontest1, yage_random_double() * 100 , yage_random_double() * 100);
      yage_button_update(buttontest1);
    }

    if (msg.type != kYageMouse) continue;
    if (msg.mouse.is_right) {
      yage_clear();
      yage_button_set_visibility(buttontest1,1);
      yage_button_update(buttontest1);
    }
    yage_player_delete(player);
    if (msg.mouse.is_middle) yage_quit();

    if (!msg.mouse.is_left) continue;
    yage_draw_pixel(msg.mouse.x, msg.mouse.y, color);
  }
}
