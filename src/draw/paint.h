#ifndef DRAW_PAINT_H
#define DRAW_PAINT_H
#include <cairo.h>
#include "point.h"
#include "color.h"
#include "font.h"
#include "linear_gradient_color.h"

using namespace yage::draw;

namespace yage {
namespace draw {

class Paint
{
  private:
    cairo_matrix_t matrix_;
    Point viewport_left_top_;
    Point viewport_right_bottom_;
    cairo_pattern_t* line_color_pattern_;
    cairo_pattern_t* fill_color_pattern_;
    cairo_pattern_t* font_color_pattern_;
    cairo_pattern_t* background_color_pattern_;
    void set_solid_color_pattern(cairo_pattern_t** pattern, Color& color);
    void set_linear_gradient_color_pattern(cairo_pattern_t** pattern, LinearGradientColor& color);
    Paint(Paint& paint){}
  public:
    double line_width;
    Font font;
    enum draw_style {
      draw_style_stroke,
      draw_style_fill,
      draw_style_stroke_fill
    };

    draw_style style;

    Paint();
    void set_translate(double tx, double ty);
    void set_rotate(double radians);
    void set_scale(double sx,double sy);
    void set_viewport(Point left_top,Point right_bottom);
    void get_viewport(Point& left_top,Point& right_bottom) const;
    void set_viewport_full_canvas();
    static bool is_viewport_full_canvas(Point& left_top,Point& right_bottom);
    bool is_viewport_full_canvas() const;

    void set_line_color(Color line_color);
    void set_line_color_linear_gradient(LinearGradientColor line_color);
    void set_fill_color(Color fill_color);
    void set_fill_color_linear_gradient(LinearGradientColor fill_color);
    void set_font_color(Color font_color);
    void set_font_color_linear_gradient(LinearGradientColor font_color);
    void set_background_color(Color bg_color);
    void set_background_color_linear_gradient(LinearGradientColor bg_color);

    cairo_pattern_t* pro_get_line_color_pattern();
    cairo_pattern_t* pro_get_fill_color_pattern();
    cairo_pattern_t* pro_get_font_color_pattern();
    cairo_pattern_t* pro_get_background_color_pattern();
    cairo_matrix_t* pro_get_cairo_matrix();
};

}
}

#endif // PAINT_H
