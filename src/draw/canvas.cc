#include "canvas.h"
#define M_PI 3.14159265358979323846
#ifdef _WIN32
#include "../platform/win32.h"
#include <cstdlib>
#endif

namespace yage {
namespace draw {

Canvas::Canvas(Window &window) : window_(&window) {
    GtkWidget *widget = window.pro_get_gtk_draw();

    surface_ = gdk_window_create_similar_surface(
            gtk_widget_get_window(widget),
            CAIRO_CONTENT_COLOR,
            gtk_widget_get_allocated_width(widget),
            gtk_widget_get_allocated_height(widget));
    brush_ = cairo_create(surface_);
    cairo_save(brush_);
    cairo_set_source_rgb(brush_, 1, 1, 1);
    cairo_paint(brush_);
    cairo_restore(brush_);
}

Canvas::Canvas(int width, int height) {
    surface_ = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    brush_ = cairo_create(surface_);
}

Canvas::Canvas(std::string filename) {
    GError *err = NULL;
    GdkPixbuf *buf = gdk_pixbuf_new_from_file(filename.c_str(), &err);
    if (err) {
        fprintf(stderr, "%s\n", err->message);
        g_error_free(err);
    }
    int width = gdk_pixbuf_get_width(buf);
    int height = gdk_pixbuf_get_height(buf);
    surface_ = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    brush_ = cairo_create(surface_);
    init_brush_();
    gdk_cairo_set_source_pixbuf(brush_, buf, 0.0, 0.0);
    cairo_paint(brush_);
    finish_brush_();
    g_object_unref(buf);
}

Canvas::~Canvas() {
    cairo_destroy(brush_);
    cairo_surface_finish(surface_);
}

void Canvas::init_brush_(void)  {
    cairo_save(brush_);
}

void Canvas::finish_brush_(void)  {
    cairo_restore(brush_);
    if (window_) window_->pro_redraw();
}

void Canvas::shape_fill_and_stroke_(ShapeProperty &shape) {
    cairo_scale(brush_, 1.0, 1.0);
    cairo_set_source_rgba(brush_,
                          shape.bgcolor.r,
                          shape.bgcolor.g,
                          shape.bgcolor.b,
                          shape.bgcolor.a);
    cairo_fill_preserve(brush_);
    shape_stroke_(shape);
}

void Canvas::shape_stroke_(ShapeProperty &shape) {
    cairo_scale(brush_, 1.0, 1.0);
    cairo_set_source_rgba(brush_,
                          shape.fgcolor.r,
                          shape.fgcolor.g,
                          shape.fgcolor.b,
                          shape.fgcolor.a);
    cairo_stroke(brush_);
}

void Canvas::draw_line(Line &line) {
    init_brush_();
    cairo_move_to(brush_, line.first.x, line.first.y);
    cairo_line_to(brush_, line.second.x, line.second.y);
    shape_stroke_(line);
    finish_brush_();
}

void Canvas::pro_draw_elliptic_arc_(Point center, double xradius, double yradius, double startangle, double endangle, ShapeProperty &shape, bool draw_sector)  {
    // Drawing Elliptic Arc procedure
    // Finally, we will draw a arc with radius of 0 at (0,0)
    init_brush_();
    cairo_set_line_width(brush_, shape.thickness);
    cairo_translate(brush_, center.x, center.y); // make center of ellipse arc (0,0)
    init_brush_();
    cairo_scale(brush_, xradius, yradius);  // scale ellipse to a circle having radius of 1
    cairo_arc(brush_, 0.0, 0.0, 1.0, startangle, endangle); // draw the 'circle arc'
    if (draw_sector) {
        cairo_line_to(brush_, 0, 0);
        cairo_close_path(brush_);
    }
    finish_brush_();
    if (draw_sector) {
        shape_fill_and_stroke_(shape);
    } else {
        shape_stroke_(shape);
    }
    finish_brush_();
}

void Canvas::draw_text(Text &text) {
    init_brush_();
    PangoLayout *layout = pango_cairo_create_layout(brush_);
#ifdef _WIN32
    char *utf_text = yage::platform::ansi_to_utf_8(text.c_str());
#else
    const char *utf_text = text.text.c_str();
#endif
    pango_layout_set_text(layout, utf_text, -1);
    pango_layout_set_font_description(layout, text.get_font().pro_get_pango_font());
    cairo_translate(brush_, text.position.x, text.position.y);
    cairo_set_source_rgba(brush_,
                          text.color.r,
                          text.color.g,
                          text.color.b,
                          text.color.a);
    pango_cairo_show_layout(brush_, layout);
#ifdef _WIN32
    free(utf_text);
#endif
    g_object_unref(layout);
    finish_brush_();
}

void Canvas::draw_poly(Poly &poly) {
    init_brush_();
    cairo_set_line_width(brush_, poly.thickness);
    for (const auto &i : poly.vertex) {
        cairo_line_to(brush_, i.x, i.y);
    }
    cairo_close_path(brush_);
    shape_fill_and_stroke_(poly);
    finish_brush_();
}

void Canvas::draw_rect(Rect &rect)  {
    init_brush_();
    const Point &a = rect.first;
    const Point &b = rect.second;
    cairo_rectangle(brush_, a.x, a.y, b.x - a.x, b.y - a.y);
    shape_fill_and_stroke_(rect);
    finish_brush_();
}

void Canvas::draw_elliptical_arc(EllipticArc &elliparc) {
    pro_draw_elliptic_arc_(elliparc.center, elliparc.xradius, elliparc.yradius, elliparc.startangle, elliparc.endangle, elliparc, false);
}

void Canvas::draw_elliptical_sector(EllipticSector &ellipsec) {
    pro_draw_elliptic_arc_(ellipsec.center, ellipsec.xradius, ellipsec.yradius, ellipsec.startangle, ellipsec.endangle, ellipsec, true);
}

void Canvas::draw_ellipse(Ellipse &ellipse) {
    pro_draw_elliptic_arc_(ellipse.center, ellipse.xradius, ellipse.yradius, 0, 2 * M_PI, ellipse, true);
}

void Canvas::draw_circle(Circle &circle)  {
    pro_draw_elliptic_arc_(circle.center, circle.radius, circle.radius, 0, 2 * M_PI, circle, true);
}

void Canvas::draw_canvas(Canvas &canvas, Point position) {
    init_brush_();
    cairo_set_source_surface(brush_, canvas.pro_get_cairo_surface(), position.x, position.y);
    cairo_paint(brush_);
    finish_brush_();
}

cairo_surface_t *Canvas::pro_get_cairo_surface(void)  {
    return surface_;
}

cairo_t *Canvas::pro_get_brush(void)  {
    return brush_;
}

void Canvas::clear(Point a, Point b, Color color) {
    init_brush_();
    cairo_set_source_rgba(brush_, color.r,
                                  color.g,
                                  color.b,
                                  color.a);
    cairo_paint(brush_);
    finish_brush_();
}

}
}
