#ifndef CANVAS_H_
#define CANVAS_H_

#include "../core/window.h"
#include "basic_shape.h"
#include "poly.h"
#include "elliptic_arc.h"
#include "rect.h"
#include "ellipse.h"
#include "circle.h"

#include <cairo.h>
#include <vector>

class Picture;
class Text;

namespace yage {
namespace draw {
using namespace core;

class Canvas : public BasicShape {
private:
    cairo_surface_t *surface_;
    cairo_t *brush_;
    Window *window_;

    void init_brush(void);
    void finish_brush(void);
    void shape_fill(BasicShape &shape) ;

public:
    // Create a canvas based on GTK-packaged yage::core::Window
    Canvas(Window &window);
    // Create a 'virtual' canvas based on memory buffer
    Canvas(int width, int height);
    ~Canvas();
    void draw_poly(Poly &poly, BasicShape *shape);
    void draw_elliptic_arc(EllipticArc &elliparc, BasicShape *shape = nullptr) ;
    void draw_canvas(Canvas &canvas);
    void draw_picture(Picture &picture);
    void draw_text(Text &text);

    void draw_rect(Rect &rect);
    void draw_ellipse(Ellipse &ellipse, BasicShape *shape = nullptr);
    void draw_circle(Circle &circle);

    cairo_surface_t *pro_get_cairo_surface(void);
    cairo_t *pro_get_brush(void);
};

}
}
#endif
