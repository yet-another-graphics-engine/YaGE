#include "../../include/yage.h"
#include <cmath>
#include <cstdlib>

void test_api_yage(void) {
  const double kPi = 3.1415926;
  yage_init(640, 480);

  yage_circle(          60, 40, 20);
  yage_circle_fill(     160, 40, 20);
  yage_circle_border(   260, 40, 20);

  yage_color_t color;
  color.r = 1, color.g = 0, color.b = 0, color.a = 1;
  yage_set_border_color(color);

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

  yage_sector(          360, 140, 20, 0 * kPi / 3, 2 * kPi / 3);
  yage_sector_fill(     460, 140, 20, 2 * kPi / 3, 4 * kPi / 3);
  yage_sector_border(   560, 140, 20, 4 * kPi / 3, 6 * kPi / 3);

  yage_arc_border(      60, 240, 20, kPi, 0);
  yage_line_border(     140, 220, 160, 240);

  yage_get_key();

  int val_int = yage_input_int("yage_input_int", nullptr);
  double val_double = yage_input_double("yage_input_double", nullptr);
  yage_dlg_font(nullptr);
  yage_dlg_color(nullptr, &color);
  yage_set_font_color(color);
  yage_printf(240, 200, "int = %d, double = %lf", val_int, val_double);

  char val_str[64];
  yage_input_scanf(nullptr, "Enter [str][num]", "%s %d", val_str, &val_int);
  yage_set_font("Microsoft YaHei", 10, true, true);
  yage_printf(240, 240, "str = %s, num = %d", val_str, val_int);

  if (yage_dlg_question(nullptr, "Save file?",
                        kYageDlgIconQuestion,
                        kYageDlgButtonYesNo) == kYageDlgResultYes) {
    yage_dlg_message(nullptr, yage_dlg_file_save(nullptr));;
  } else {
    yage_dlg_message(nullptr, yage_dlg_file_open(nullptr));;
  }

  yage_message_t msg;
  while (yage_get_message(&msg, 0)) {
    if (msg.type != YageMouse) continue;
    if (msg.mouse.is_right) yage_clear();
    if (msg.mouse.is_middle) yage_quit();

    if (!msg.mouse.is_left) continue;
    yage_draw_pixel(msg.mouse.x, msg.mouse.y, color);
  }

}
