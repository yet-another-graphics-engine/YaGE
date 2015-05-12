#ifndef CANVAS_H_
#define CANVAS_H_

#include "../core/window.h"
#include "shape_property.h"
#include "poly.h"
#include "elliptic_arc.h"
#include "rect.h"
#include "ellipse.h"
#include "circle.h"
#include "text.h"

#include <cairo.h>
#include <vector>

class Picture;

namespace yage {
namespace core {
class Window;
}

namespace draw {

using namespace core;

class Canvas : public ShapeProperty {
private:
    cairo_surface_t *surface_;
    cairo_t *brush_;
    Window *window_;

    void init_brush_(void);
    void finish_brush_(void);
    void shape_fill_(ShapeProperty &shape);
    void pro_draw_poly_(BasePoly &poly, ShapeProperty &shape);
    void pro_draw_elliptic_arc_(BaseEllipticArc &elliparc, ShapeProperty &shape);
    void pro_draw_ellipse_(BaseEllipse &ellipse, ShapeProperty &shape);

public:
    // Create a canvas based on GTK-packaged yage::core::Window
    Canvas(Window &window);
    // Create a 'virtual' canvas based on memory buffer
    Canvas(int width, int height);
    ~Canvas();
    void draw_poly(Poly &poly);
    void draw_rect(Rect &rect);
    void draw_elliptical_arc(EllipticArc &ellparc);
    void draw_ellipse(Ellipse &ellipse);
    void draw_circle(Circle &circle);
    void draw_canvas(Canvas &canvas);
    void draw_picture(Picture &picture);
    void draw_text(Text &text);

    cairo_surface_t *pro_get_cairo_surface(void);
    cairo_t *pro_get_brush(void);
};

}
}
#endif
