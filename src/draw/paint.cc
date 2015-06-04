#include "paint.h"

namespace yage {
namespace draw {

Paint::Paint() {
  line_width = 2;
  line_color = Color(0, 0, 0, 1);
  fill_color = Color(1, 1, 1, 1);
  font_color = Color(0, 0, 0, 1);
  background_color = Color(1, 1, 1, 1);
  cairo_matrix_init_translate(&matrix_, 0, 0);
  cairo_matrix_init_rotate(&matrix_, 0);
  cairo_matrix_init_scale(&matrix_, 1.0, 1.0);
  set_viewport_full_canvas();
}

void Paint::set_translate(double tx, double ty) {
  cairo_matrix_init_translate(&matrix_, 0, 0);
  cairo_matrix_translate(&matrix_, tx, ty);
}

void Paint::set_rotate(double radians) {
  cairo_matrix_init_rotate(&matrix_, 0);
  cairo_matrix_rotate(&matrix_, radians);
}

void Paint::set_scale(double sx, double sy) {
  cairo_matrix_init_scale(&matrix_, 1.0, 1.0);
  cairo_matrix_scale(&matrix_, sx, sy);
}

void Paint::get_viewport(Point& left_top,Point& right_bottom) const {
  left_top.x = viewport_left_top_.x;
  left_top.y = viewport_left_top_.y;
  right_bottom.x = viewport_right_bottom_.x;
  right_bottom.y = viewport_right_bottom_.y;
}

void Paint::set_viewport(Point left_top, Point right_bottom) {
  if(is_viewport_full_canvas(left_top,right_bottom))
    set_viewport_full_canvas();
  else
  {
    viewport_left_top_ = left_top;
    viewport_right_bottom_ = right_bottom;
  }
}

bool Paint::is_viewport_full_canvas(Point& left_top, Point& right_bottom) {
  if(left_top.x != -1 || left_top.y != -1)
    return false;
  if(right_bottom.x != -1 || right_bottom.y != -1)
    return false;
  return true;
}

bool Paint::is_viewport_full_canvas() const {
  if(viewport_left_top_.x!=-1 || viewport_left_top_.y!=-1)
    return false;
  if(viewport_right_bottom_.x!=-1 || viewport_right_bottom_.y!=-1)
    return false;
  return true;
}

void Paint::set_viewport_full_canvas() {
  viewport_left_top_.x=viewport_left_top_.y=-1;
  viewport_right_bottom_.x=viewport_right_bottom_.y=-1;
}

const cairo_matrix_t* Paint::pro_get_cairo_matrix() const {
  return &matrix_;
}

}
}
