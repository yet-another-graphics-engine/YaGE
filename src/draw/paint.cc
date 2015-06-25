#include "paint.h"

namespace yage {
namespace draw {

Paint::Paint() {
  line_width = 2.0;
  line_color_pattern_ = nullptr;
  fill_color_pattern_ = nullptr;
  font_color_pattern_ = nullptr;
  background_color_pattern_ = nullptr;
  style = draw_style_stroke;

  Color white(1, 1, 1, 1);
  Color black(0, 0, 0, 1);
  set_solid_color_pattern(&line_color_pattern_, black);
  set_solid_color_pattern(&fill_color_pattern_, white);
  set_solid_color_pattern(&font_color_pattern_, black);
  set_solid_color_pattern(&background_color_pattern_, white);
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

void Paint::set_solid_color_pattern(cairo_pattern_t** pattern, Color& color) {
  if(*pattern != nullptr)
    cairo_pattern_destroy(*pattern);
  *pattern = cairo_pattern_create_rgba(color.r, color.g, color.b, color.a);
}

void Paint::set_linear_gradient_color_pattern(cairo_pattern_t** pattern, LinearGradientColor& color) {
  if(*pattern != nullptr)
    cairo_pattern_destroy(*pattern);
  *pattern = cairo_pattern_create_linear(color.start_point.x, color.start_point.y,
                                         color.end_point.x, color.end_point.y);
  cairo_pattern_add_color_stop_rgba(*pattern, 0.0, color.start_color.r, color.start_color.g,
                                    color.start_color.b, color.start_color.a);
  cairo_pattern_add_color_stop_rgba(*pattern, 1.0, color.end_color.r, color.end_color.g,
                                    color.end_color.b, color.end_color.a);
}

void Paint::set_line_color(Color line_color) {
  set_solid_color_pattern(&line_color_pattern_, line_color);
}

void Paint::set_line_color_linear_gradient(LinearGradientColor line_color) {
  set_linear_gradient_color_pattern(&line_color_pattern_, line_color);
}

void Paint::set_fill_color(Color fill_color) {
  set_solid_color_pattern(&fill_color_pattern_, fill_color);
}

void Paint::set_fill_color_linear_gradient(LinearGradientColor fill_color) {
  set_linear_gradient_color_pattern(&fill_color_pattern_, fill_color);
}

void Paint::set_font_color(Color font_color) {
  set_solid_color_pattern(&font_color_pattern_, font_color);
}

void Paint::set_font_color_linear_gradient(LinearGradientColor font_color) {
  set_linear_gradient_color_pattern(&font_color_pattern_, font_color);
}

void Paint::set_background_color(Color bg_color) {
  set_solid_color_pattern(&background_color_pattern_, bg_color);
}

void Paint::set_background_color_linear_gradient(LinearGradientColor bg_color) {
  set_linear_gradient_color_pattern(&background_color_pattern_, bg_color);
}

cairo_pattern_t* Paint::pro_get_line_color_pattern() {
  return line_color_pattern_;
}

cairo_pattern_t* Paint::pro_get_fill_color_pattern() {
  return fill_color_pattern_;
}

cairo_pattern_t* Paint::pro_get_font_color_pattern() {
  return font_color_pattern_;
}

cairo_pattern_t* Paint::pro_get_background_color_pattern() {
  return background_color_pattern_;
}

cairo_matrix_t* Paint::pro_get_cairo_matrix() {
  return &matrix_;
}


}
}
