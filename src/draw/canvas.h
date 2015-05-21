#ifndef DRAW_CANVAS_H_
#define DRAW_CANVAS_H_

#include "../window/window.h"
#include "shape_property.h"
#include "poly.h"
#include "elliptic_arc.h"
#include "elliptic_sector.h"
#include "rect.h"
#include "ellipse.h"
#include "circle.h"
#include "text.h"
#include "line.h"
#include "color.h"

#include <cairo.h>
#include <vector>

using namespace yage::draw;

namespace yage {
namespace window {
class Window;
}


namespace draw {

class Canvas {
    private:
        cairo_surface_t *surface_;
        cairo_t *brush_;
        cairo_surface_t *buffer_surface_;
        cairo_t *buffer_brush_;

        Color bg_color_;
        int width_;
        int height_;
        Point viewport_left_top_;
        Point viewport_right_bottom_;

        void shape_fill_and_stroke_(ShapeProperty &shape);
        void shape_stroke_(ShapeProperty &shape);
        void pro_draw_elliptic_arc_(Point center, double xradius, double yradius, double startangle, double endangle, ShapeProperty &shape, bool draw_sector = false);
    public:
        // Create a 'virtual' canvas based on memory buffer
        Canvas(int width, int height,Color bg_color=Color(1,1,1,1));
        // Create a 'virtual' canvas based on a specific picture
        Canvas(std::string filename,Color bg_color=Color(1,1,1,1));
        ~Canvas();

        Color get_bg_color(void);
        void set_bg_color(Color color);

        void set_viewport(Point left_top,Point right_bottom);
        void get_viewport(Point* left_top,Point* right_bottom);
        void update_canvas(void);

        void draw_line(Line &line);
        void draw_poly(Poly &poly);
        void draw_rect(Rect &rect);
        void draw_elliptical_arc(EllipticArc &elliparc);
        void draw_elliptical_sector(EllipticSector &ellpsec);
        void draw_ellipse(Ellipse &ellipse);
        void draw_circle(Circle &circle);
        // position indicates the left-top position
        void draw_canvas(Canvas &canvas, Point position);
        void draw_text(Text &text);
        void clear_all(void);
        void clear_viewport(void);

        cairo_surface_t *pro_get_cairo_surface(void);
        cairo_t *pro_get_brush(void);
};

}
}
#endif
