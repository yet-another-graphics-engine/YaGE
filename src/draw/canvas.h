#ifndef CANVAS_H_
#define CANVAS_H_

#include "../core/window.h"
#include "shape_property.h"
#include "poly.h"
#include "elliptic_arc.h"
#include "elliptic_sector.h"
#include "rect.h"
#include "ellipse.h"
#include "circle.h"
#include "text.h"
#include "line.h"

#include <cairo.h>
#include <vector>

namespace yage {
namespace core {
class Window;
}

namespace draw {

using namespace core;

class Canvas {
private:
    cairo_surface_t *surface_;
    cairo_t *brush_;
    Window *window_;

    void init_brush_(void);
    void finish_brush_(void);
    void shape_fill_and_stroke_(ShapeProperty &shape);
    void shape_stroke_(ShapeProperty &shape);
    void pro_draw_elliptic_arc_(Point center, double xradius, double yradius, double startangle, double endangle, ShapeProperty &shape, bool draw_sector = false);

public:
    // Create a canvas based on GTK-packaged yage::core::Window
    Canvas(Window &window);
    // Create a 'virtual' canvas based on memory buffer
    Canvas(int width, int height);
    // Create a 'virtual' canvas based on a specific picture
    Canvas(std::string filename);
    ~Canvas();
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
    void clear(Point a = Point(), Point b = Point(), Color color=Color(1,1,1,1));

    cairo_surface_t *pro_get_cairo_surface(void);
    cairo_t *pro_get_brush(void);
};

}
}
#endif
