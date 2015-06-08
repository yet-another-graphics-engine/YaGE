#include <cstring>
#include <sstream>
#include "../../include/yage.h"
#include "../window/window.h"
#include "../dialog/color_chooser_dlg.h"
#include "../dialog/font_chooser_dlg.h"
#include "../dialog/file_chooser_dlg.h"
#include "../dialog/message_dlg.h"
#include "../dialog/input_dlg.h"

using namespace yage;
namespace {
  const draw::Color kTransparentColor(0, 0, 0, 0);
  const size_t kMaxTextBuffer = 2048;

  window::Window *g_window = nullptr;
  draw::Canvas *g_canvas = nullptr;
  draw::Paint *g_paint = nullptr;
  draw::Color g_fill_color;
  draw::Color g_border_color;

  inline void prepare_color(bool is_fill, bool is_border) {
    g_paint->line_color = is_border ? g_border_color : kTransparentColor;
    g_paint->fill_color = is_fill ? g_fill_color : kTransparentColor;
  }

  inline void draw_circle(double x, double y, double r) {
    draw::Circle circle;
    circle.center = draw::Point(x, y);
    circle.radius = r;
    g_canvas->draw_circle(circle);
    g_window->update();
  }

  inline void draw_ellipse(double x, double y,
                           double radius_x, double radius_y) {
    draw::Ellipse ellipse;
    ellipse.center = draw::Point(x, y);
    ellipse.xradius = radius_x;
    ellipse.yradius = radius_y;
    g_canvas->draw_ellipse(ellipse);
    g_window->update();
  }

  inline void draw_rectangle(double x1, double y1, double x2, double y2) {
    draw::Rect rect;
    rect.first = draw::Point(x1, y1);
    rect.second = draw::Point(x2, y2);
    g_canvas->draw_rect(rect);
    g_window->update();
  }

  inline void draw_sector(double x, double y, double r,
                          double angle_begin, double angle_end) {
    draw::EllipticSector sector;
    sector.center.x = x;
    sector.center.y = y;
    sector.xradius = sector.yradius = r;
    sector.startangle = angle_begin;
    sector.endangle = angle_end;
    g_canvas->draw_elliptical_sector(sector);
    g_window->update();
  }
}

extern "C" {

void yage_init(int width, int height) {
  if (g_window) delete g_window;
  if (g_canvas) delete g_canvas;
  if (g_paint) delete g_paint;

  g_window = new window::Window(width, height);
  g_canvas = new draw::Canvas(width, height);
  g_paint = new draw::Paint;

  g_fill_color = draw::Color(0.5, 0.5, 0.5, 1);
  g_border_color = draw::Color(0, 0, 0, 1);
  g_paint->background_color = Color(1, 1, 1, 1);

  g_window->set_canvas(*g_canvas);
}

void yage_quit(void) {
  window::Window::quit();
}

void yage_clear(void) {
  g_canvas->clear_all();
}

void yage_draw_pixel(double x, double y) {
  // FIXME
}

void yage_set_font(const char *family, int size, int bold, int italic) {
  if (family)       g_paint->font.set_font_family(family);
  if (size > 0)     g_paint->font.set_size(size);
  if (bold >= 0)    g_paint->font.set_bold_status(bold ? true : false);
  if (italic >= 0)  g_paint->font.set_italic_status(italic ? true : false);
}

void yage_set_fill_color(struct yage_color_t fill_color) {
  g_fill_color.r = fill_color.r;
  g_fill_color.g = fill_color.g;
  g_fill_color.b = fill_color.b;
  g_fill_color.a = fill_color.a;
}

void yage_set_border_color(struct yage_color_t border_color) {
  g_border_color.r = border_color.r;
  g_border_color.g = border_color.g;
  g_border_color.b = border_color.b;
  g_border_color.a = border_color.a;
}

void yage_set_border_thickness(double thickness) {
  g_paint->line_width = thickness;
}

void yage_circle(double x, double y, double r) {
  prepare_color(true, true);
  draw_circle(x, y, r);
}

void yage_circle_fill(double x, double y, double r) {
  prepare_color(true, false);
  draw_circle(x, y, r);
}

void yage_circle_border(double x, double y, double r) {
  prepare_color(false, true);
  draw_circle(x, y, r);
}

void yage_ellipse(double x, double y, double radius_x, double radius_y) {
  prepare_color(true, true);
  draw_ellipse(x, y, radius_x, radius_y);
}

void yage_ellipse_fill(double x, double y, double radius_x, double radius_y) {
  prepare_color(true, false);
  draw_ellipse(x, y, radius_x, radius_y);
}

void yage_ellipse_border(double x, double y, double radius_x, double radius_y) {
  prepare_color(false, true);
  draw_ellipse(x, y, radius_x, radius_y);
}

void yage_rectangle(double x1, double y1, double x2, double y2) {
  prepare_color(true, true);
  draw_rectangle(x1, y1, x2, y2);
}

void yage_rectangle_fill(double x1, double y1, double x2, double y2) {
  prepare_color(true, false);
  draw_rectangle(x1, y1, x2, y2);
}

void yage_rectangle_border(double x1, double y1, double x2, double y2) {
  prepare_color(false, true);
  draw_rectangle(x1, y1, x2, y2);
}

void yage_sector(double x, double y, double r,
                 double angle_begin, double angle_end) {
  prepare_color(true, true);
  draw_sector(x, y, r, angle_begin, angle_end);
}

void yage_sector_fill(double x, double y, double r,
                      double angle_begin, double angle_end) {
  prepare_color(true, false);
  draw_sector(x, y, r, angle_begin, angle_end);
}

void yage_sector_border(double x, double y, double r,
                        double angle_begin, double angle_end) {
  prepare_color(false, true);
  draw_sector(x, y, r, angle_begin, angle_end);
}

void yage_arc_border(double x, double y, double r,
                     double angle_begin, double angle_end) {
  prepare_color(true, true);

  draw::EllipticSector arc;
  arc.center = draw::Point(x, y);
  arc.xradius = arc.yradius = r;
  arc.startangle = angle_begin;
  arc.endangle = angle_end;
  g_canvas->draw_elliptical_sector(arc, *g_paint);
  g_window->update();
}

void yage_line_border(double x1, double y1, double x2, double y2) {
  prepare_color(true, true);
  draw::Line line(draw::Point(x1, y1), draw::Point(x2, y2));
  g_canvas->draw_line(line);
  g_window->update();
}

void yage_printf(double x, double y, const char *format, ...) {
  char buf[kMaxTextBuffer];

  va_list args;
  va_start(args, format);
  vsnprintf(buf, sizeof(buf), format, args);
  va_end(args);

  yage::draw::Text text(buf);
  text.position = draw::Point(x, y);
  g_canvas->draw_text(text, *g_paint);
  g_window->update();
}

void yage_get_message(struct yage_message_t *msg, int wait_ms) {
  // FIXME: add wait_ms support
  window::Window::poll(*reinterpret_cast<window::Message *>(msg));
}

int  yage_get_key(void) {
  window::Message msg;
  while (window::Window::poll(msg)) {
    if (msg.type != msg.type_kbd) continue;
    return msg.kbd.keyval;
  }
  return -1;
}

int  yage_dlg_font(const char *title) {
  dialog::FontChooserDlg font_dlg(title, *g_window);
  return font_dlg.show(g_paint->font);
}

int  yage_dlg_color(const char *title, struct yage_color_t *color) {
  dialog::ColorChooserDlg font_dlg(title, *g_window);
  draw::Color internal_coler;

  int ret = font_dlg.show(internal_coler);
  color->r = internal_coler.r;
  color->g = internal_coler.g;
  color->b = internal_coler.b;
  color->a = internal_coler.a;
  return ret;
}

char *yage_dlg_file_save(const char *title) {
  dialog::FileChooserDlg fc_dlg(dialog::FileChooserDlg::action_type_save,
                                title, *g_window);
  std::string path;
  if (!fc_dlg.show(path)) return nullptr;
  return strdup(path.c_str());
}

char *yage_dlg_file_open(const char *title) {
  dialog::FileChooserDlg fc_dlg(dialog::FileChooserDlg::action_type_open,
                                title,
                                *g_window);
  std::string path;
  if (!fc_dlg.show(path)) return nullptr;
  return strdup(path.c_str());
}

void yage_dlg_message(const char *title, const char *message) {
  using dialog::MessageDlg;
  MessageDlg msg_dlg(MessageDlg::button_type_ok,
                     MessageDlg::icon_type_none,
                     *g_window);
  msg_dlg.set_title(title);
  msg_dlg.set_message(message);
  msg_dlg.show();
}

yage_dlg_result_t yage_dlg_question(const char *title,
                                    const char *message,
                                    yage_dlg_icon_t icon,
                                    yage_dlg_button_t button) {
  using dialog::MessageDlg;
  MessageDlg msg_dlg(static_cast<dialog::MessageDlg::button_type>(button),
                     static_cast<dialog::MessageDlg::icon_type>(icon),
                     *g_window);
  msg_dlg.set_title(title);
  msg_dlg.set_message(message);

  return static_cast<yage_dlg_result_t>(msg_dlg.show());
}

int yage_input_int(const char *title, const char *message) {
  dialog::InputDlg dlg(title, *g_window);
  dlg.set_message(message);

  std::string str;
  dlg.show(str);

  int ret;
  std::stringstream stream(str);
  stream >> ret;
  return ret;
}

double yage_input_double(const char *title, const char *message) {
  dialog::InputDlg dlg(title, *g_window);
  dlg.set_message(message);

  std::string str;
  dlg.show(str);

  double ret;
  std::stringstream stream(str);
  stream >> ret;
  return ret;
}

char *yage_input_line(const char *title, const char *message) {
  dialog::InputDlg dlg(title, *g_window);
  dlg.set_message(message);

  std::string str;
  dlg.show(str);
  return strdup(str.c_str());
}

int yage_input_scanf(const char *title, const char *message,
                     const char *format, ...) {
  dialog::InputDlg dlg(title, *g_window);
  dlg.set_message(message);

  std::string str;
  dlg.show(str);

  va_list args;
  va_start(args, format);
  int ret = vsscanf(str.c_str(), format, args);
  va_end(args);

  return ret;
}

}
