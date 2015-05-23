#ifndef DRAW_CANVAS_H_
#define DRAW_CANVAS_H_

#include "text.h"
#include "color.h"
#include "paint.h"
#include "shape.h"

#include <cairo.h>
#include <pango/pango.h>
#include <gdk/gdk.h>
#include <vector>

using namespace yage::draw;

namespace yage {
namespace draw {

class Canvas {
    private:
        cairo_surface_t *surface_;
        cairo_t *brush_;

        Paint paint_;
        int width_;
        int height_;

        void init_brush(void);
        void shape_fill_and_stroke_(void);
        void shape_stroke_(void);
        void init_brush(const Paint &paint);
        void shape_fill_and_stroke_(const Paint &paint);
        void shape_stroke_(const Paint &paint);
        void pro_draw_elliptic_arc_(Point center, double xradius, double yradius, double startangle, double endangle,
                                    const Paint &paint, bool draw_sector = false);
    public:
        // Create a 'virtual' canvas based on memory buffer
        Canvas(int width, int height);
        // Create a 'virtual' canvas based on a specific picture
        Canvas(std::string filename);
        ~Canvas();
        
        void draw_line(Line &line, const Paint &paint);
        void draw_poly(Poly &poly, const Paint &paint);
        void draw_rect(Rect &rect, const Paint &paint);
        void draw_elliptical_arc(EllipticArc &elliparc, const Paint &paint);
        void draw_elliptical_sector(EllipticSector &ellpsec, const Paint &paint);
        void draw_ellipse(Ellipse &ellipse, const Paint &paint);
        void draw_circle(Circle &circle, const Paint &paint);
        // position indicates the left-top position
        void draw_canvas(Canvas &canvas, Point position, const Paint &paint);
        void draw_text(Text &text, const Paint &paint);
        void clear_all(const Paint &paint);
        void clear_viewport(const Paint &paint);

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
