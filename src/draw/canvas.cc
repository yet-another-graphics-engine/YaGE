#include "canvas.h"
#define M_PI 3.14159265358979323846
#ifdef _WIN32
#include "../util/mswin.h"
#include <cstdlib>
#endif

namespace yage {
namespace draw {

Canvas::Canvas(int width, int height) {
    width_ = width;
    height_ = height;

    surface_ = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    brush_ = cairo_create(surface_);
    clear_all();
}

Canvas::Canvas(std::string filename) {
    GError *err = NULL;
    GdkPixbuf *buf = gdk_pixbuf_new_from_file(filename.c_str(), &err);
    if (err) {
        fprintf(stderr, "%s\n", err->message);
        g_error_free(err);
    }
    width_ = gdk_pixbuf_get_width(buf);
    height_ = gdk_pixbuf_get_height(buf);

    surface_ = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width_, height_);
    brush_ = cairo_create(surface_);

    gdk_cairo_set_source_pixbuf(brush_, buf, 0.0, 0.0);
    cairo_paint(brush_);

    g_object_unref(buf);
}

Canvas::~Canvas() {
    cairo_destroy(brush_);
    cairo_surface_destroy(surface_);
    brush_ = nullptr;
    surface_ = nullptr;
}

void Canvas::init_brush(void)
{
    cairo_reset_clip(brush_);
    if(!paint_.is_viewport_full_canvas())
    {
        Point left_top, right_bottom;
        paint_.get_viewport(left_top, right_bottom);
        cairo_rectangle(brush_, left_top.x, left_top.y,
                        right_bottom.x-left_top.x+1,
                        right_bottom.y-left_top.y+1);
        cairo_clip(brush_);
    }
    cairo_save(brush_);
    cairo_set_matrix(brush_, paint_.pro_get_cairo_matrix());
}


void Canvas::shape_fill_and_stroke_(const Paint &paint) {
    cairo_scale(brush_, 1.0, 1.0);
    cairo_set_source_rgba(brush_,
                          paint.fill_color.r,
                          paint.fill_color.g,
                          paint.fill_color.b,
                          paint.fill_color.a);
    cairo_fill_preserve(brush_);
    shape_stroke_(paint);
}

void Canvas::shape_stroke_(const Paint &paint) {
    cairo_scale(brush_, 1.0, 1.0);
    cairo_set_line_width(brush_, paint.line_width);
    cairo_set_source_rgba(brush_,
                          paint.line_color.r,
                          paint.line_color.g,
                          paint.line_color.b,
                          paint.line_color.a);
    cairo_stroke(brush_);
}

void Canvas::draw_line(Line &line, const Paint& paint) {
    init_brush();
    cairo_move_to(brush_, line.first.x, line.first.y);
    cairo_line_to(brush_, line.second.x, line.second.y);
    shape_stroke_(paint);
    cairo_restore(brush_);
}

void Canvas::pro_draw_elliptic_arc_(Point center, double xradius, double yradius,
                                    double startangle, double endangle, bool draw_sector, const Paint &paint)  {
    // Drawing Elliptic Arc procedure
    // Finally, we will draw a arc with radius of 0 at (0, 0)
    init_brush();
    //cairo_set_line_width(brush_, paint.line_width);
    cairo_translate(brush_, center.x, center.y); // make center of ellipse arc (0, 0)

    cairo_save(brush_);
    cairo_scale(brush_, xradius, yradius);  // scale ellipse to a circle having radius of 1
    cairo_arc(brush_, 0.0, 0.0, 1.0, startangle, endangle); // draw the 'circle arc'
    if (draw_sector && endangle != 2 * M_PI) {
        cairo_line_to(brush_, 0, 0);
        cairo_close_path(brush_);
    }

    cairo_restore(brush_);
    if (draw_sector) {
        shape_fill_and_stroke_(paint);
    } else {
        shape_stroke_(paint);
    }
    cairo_restore(brush_);
}

void Canvas::draw_text(Text &text, const Paint &paint) {
    init_brush();
    PangoLayout *layout = pango_cairo_create_layout(brush_);
#ifdef _WIN32
    char *utf_text = yage::util::ansi_to_utf_8(text.text.c_str());
#else
    const char *utf_text = text.text.c_str();
#endif
    pango_layout_set_text(layout, utf_text, -1);
    pango_layout_set_font_description(layout, text.get_font().pro_get_pango_font());
    cairo_translate(brush_, text.position.x, text.position.y);
    cairo_set_source_rgba(brush_,
                          paint.line_color.r,
                          paint.line_color.g,
                          paint.line_color.b,
                          paint.line_color.a);
    pango_cairo_show_layout(brush_, layout);
#ifdef _WIN32
    free(utf_text);
#endif
    g_object_unref(layout);
    cairo_restore(brush_);
}

void Canvas::draw_poly(Poly &poly, const Paint &paint) {
    init_brush();
    //cairo_set_line_width(brush_, poly.thickness);
    for (const auto &i : poly.vertex) {
        cairo_line_to(brush_, i.x, i.y);
    }
    cairo_close_path(brush_);
    shape_fill_and_stroke_(paint);
    cairo_restore(brush_);
}

void Canvas::draw_rect(Rect &rect, const Paint &paint) {
    init_brush();
    const Point &a = rect.first;
    const Point &b = rect.second;
    cairo_rectangle(brush_, a.x, a.y, b.x - a.x, b.y - a.y);
    shape_fill_and_stroke_(paint);
    cairo_restore(brush_);
}

void Canvas::draw_elliptical_arc(EllipticArc &elliparc, const Paint &paint) {
    pro_draw_elliptic_arc_(elliparc.center, elliparc.xradius, elliparc.yradius, elliparc.startangle, elliparc.endangle, false, paint);
}

void Canvas::draw_elliptical_sector(EllipticSector &ellipsec, const Paint &paint) {
    pro_draw_elliptic_arc_(ellipsec.center, ellipsec.xradius, ellipsec.yradius, ellipsec.startangle, ellipsec.endangle, true, paint);
}

void Canvas::draw_ellipse(Ellipse &ellipse, const Paint &paint) {
    pro_draw_elliptic_arc_(ellipse.center, ellipse.xradius, ellipse.yradius, 0, 2 * M_PI, true, paint);
}

void Canvas::draw_circle(Circle &circle, const Paint &paint) {
    pro_draw_elliptic_arc_(circle.center, circle.radius, circle.radius, 0, 2 * M_PI, true, paint);
}

void Canvas::draw_canvas(Canvas &canvas, Point position, const Paint &paint) {
    init_brush();
    cairo_set_source_surface(brush_, canvas.pro_get_cairo_surface(), position.x, position.y);
    cairo_paint(brush_);
    cairo_restore(brush_);
}

cairo_surface_t *Canvas::pro_get_cairo_surface(void) {
    return surface_;
}

cairo_t *Canvas::pro_get_brush(void) {
    return brush_;
}

void Canvas::clear_all(const Paint &paint) {
    cairo_reset_clip(brush_);
    cairo_save(brush_);
    cairo_set_source_rgba(brush_, paint.background_color.r,
                                  paint.background_color.g,
                                  paint.background_color.b,
                                  paint.background_color.a);
    cairo_paint(brush_);
    cairo_restore(brush_);
}

void Canvas::clear_viewport(const Paint &paint){
    init_brush();
    cairo_set_source_rgba(brush_, paint.background_color.r,
                                  paint.background_color.g,
                                  paint.background_color.b,
                                  paint.background_color.a);
    cairo_paint(brush_);
    cairo_restore(brush_);
}

}
}
