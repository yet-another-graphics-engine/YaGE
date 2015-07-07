#include <string>
#include "canvas.h"
#include "../util/encoding.h"

namespace yage {
namespace draw {

Canvas::Canvas(int width, int height) : paint_() {
    width_ = width;
    height_ = height;

    surface_ = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    brush_ = cairo_create(surface_);
}

Canvas::Canvas(const std::string &filename) : paint_() {
    GError *err = NULL;
    std::string utf_8_filename = yage::util::convert_string(filename);
    GdkPixbuf *buf = gdk_pixbuf_new_from_file(utf_8_filename.c_str(), &err);
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

Canvas::Canvas(Canvas& canvas)
{
    width_=canvas.width_;
    height_=canvas.height_;
    paint_=canvas.paint_;
    surface_=cairo_image_surface_create(CAIRO_FORMAT_ARGB32,width_,height_);
    brush_=cairo_create(surface_);
    cairo_save(brush_);

    cairo_set_source_surface(brush_,canvas.surface_,0,0);
    cairo_paint(brush_);

    cairo_restore(brush_);
}

Canvas::~Canvas() {
    cairo_destroy(brush_);
    cairo_surface_destroy(surface_);
}

void Canvas::get_size(int& width,int& height) {
    width=width_;
    height=height_;
}

void Canvas::init_brush(Paint &paint) {
    cairo_reset_clip(brush_);
    if (!paint.is_viewport_full_canvas()) {
        Point left_top, right_bottom;
        paint.get_viewport(left_top, right_bottom);
        cairo_rectangle(brush_, left_top.x, left_top.y,
                        right_bottom.x-left_top.x+1,
                        right_bottom.y-left_top.y+1);
        cairo_clip(brush_);
    }
    cairo_save(brush_);
    cairo_set_matrix(brush_, paint.pro_get_cairo_matrix());
}

void Canvas::shape_fill_and_stroke_(Paint &paint) {
    if(paint.style != Paint::draw_style_stroke)
    {
      //cairo_scale(brush_, 1.0, 1.0);
      cairo_set_source(brush_, paint.pro_get_fill_color_pattern());
      if(paint.style == Paint::draw_style_fill)
        cairo_fill(brush_);
      else
        cairo_fill_preserve(brush_);
    }
    shape_stroke_(paint);
}

void Canvas::shape_stroke_(Paint &paint) {
    if(paint.style != Paint::draw_style_fill)
    {
      //cairo_scale(brush_, 1.0, 1.0);
      cairo_set_line_width(brush_, paint.line_width);
      cairo_set_source(brush_, paint.pro_get_line_color_pattern());
      cairo_stroke(brush_);
    }
}

void Canvas::draw_line(Line &line, Paint& paint) {
    init_brush(paint);
    cairo_move_to(brush_, line.first.x, line.first.y);
    cairo_line_to(brush_, line.second.x, line.second.y);
    shape_stroke_(paint);
    cairo_restore(brush_);
}

void Canvas::draw_line(Line &line) {
    draw_line(line, paint_);
}

void Canvas::pro_draw_elliptic_arc_(Point center,
                                    double xradius, double yradius,
                                    double startangle, double endangle,
                                    Paint &paint, bool draw_sector) {
    // Drawing Elliptic Arc procedure
    // Finally, we will draw a arc with radius of 0 at (0, 0)
    init_brush(paint);
    // make center of ellipse arc (0, 0)
    cairo_translate(brush_, center.x, center.y);
    // scale ellipse to a circle having radius of 1
    cairo_save(brush_);
    cairo_scale(brush_, xradius, yradius);
    // draw the 'circle arc'
    cairo_arc(brush_, 0.0, 0.0, 1.0, startangle, endangle);
    if (draw_sector && endangle != 2 * M_PI) {
        cairo_line_to(brush_, 0, 0);
        cairo_close_path(brush_);
    }

    cairo_restore(brush_);
    cairo_restore(brush_);
    cairo_save(brush_);
    if (draw_sector) {
        shape_fill_and_stroke_(paint);
    } else {
        shape_stroke_(paint);
    }
    cairo_restore(brush_);
}

void Canvas::draw_text(Text &text, Paint &paint) {
    init_brush(paint);
    PangoLayout *layout = pango_cairo_create_layout(brush_);
    pango_layout_set_text(layout, text.get_text().c_str(), -1);
    pango_layout_set_font_description(layout,
                                      paint.font.pro_get_pango_font());
    cairo_translate(brush_, text.position.x, text.position.y);
    cairo_set_source(brush_, paint.pro_get_font_color_pattern());
    pango_cairo_show_layout(brush_, layout);
    g_object_unref(layout);
    cairo_restore(brush_);
}

void Canvas::draw_text(Text &text) {
    draw_text(text, paint_);
}

void Canvas::draw_poly(Poly &poly, Paint &paint) {
    init_brush(paint);
    for (Poly::Vertexes::iterator p = poly.vertex.begin();
        p != poly.vertex.end();
        ++p) {
        cairo_line_to(brush_, p->x, p->y);
    }
    cairo_close_path(brush_);
    shape_fill_and_stroke_(paint);
    cairo_restore(brush_);
}

void Canvas::draw_poly(Poly &poly) {
    draw_poly(poly, paint_);
}

void Canvas::draw_rect(Rect &rect, Paint &paint) {
    init_brush(paint);
    const Point &a = rect.first;
    const Point &b = rect.second;
    cairo_rectangle(brush_, a.x, a.y, b.x - a.x, b.y - a.y);
    shape_fill_and_stroke_(paint);
    cairo_restore(brush_);
}

void Canvas::draw_rect(Rect &rect) {
    draw_rect(rect, paint_);
}

void Canvas::draw_elliptical_arc(EllipticArc &elliparc, Paint &paint) {
    pro_draw_elliptic_arc_(elliparc.center,
                           elliparc.xradius, elliparc.yradius,
                           elliparc.startangle, elliparc.endangle,
                           paint, false);
}

void Canvas::draw_elliptical_arc(EllipticArc &elliparc) {
    pro_draw_elliptic_arc_(elliparc.center,
                           elliparc.xradius, elliparc.yradius,
                           elliparc.startangle, elliparc.endangle,
                           paint_, false);
}

void Canvas::draw_elliptical_sector(EllipticSector &ellipsec,
                                    Paint &paint) {
    pro_draw_elliptic_arc_(ellipsec.center,
                           ellipsec.xradius, ellipsec.yradius,
                           ellipsec.startangle, ellipsec.endangle,
                           paint, true);
}

void Canvas::draw_elliptical_sector(EllipticSector &ellipsec) {
    pro_draw_elliptic_arc_(ellipsec.center,
                           ellipsec.xradius, ellipsec.yradius,
                           ellipsec.startangle, ellipsec.endangle,
                           paint_, true);
}

void Canvas::draw_ellipse(Ellipse &ellipse, Paint &paint) {
    pro_draw_elliptic_arc_(ellipse.center,
                           ellipse.xradius, ellipse.yradius,
                           0, 2 * M_PI,
                           paint, true);
}

void Canvas::draw_ellipse(Ellipse &ellipse) {
    pro_draw_elliptic_arc_(ellipse.center,
                           ellipse.xradius, ellipse.yradius,
                           0, 2 * M_PI,
                           paint_, true);
}

void Canvas::draw_circle(Circle &circle, Paint &paint) {
    pro_draw_elliptic_arc_(circle.center,
                           circle.radius, circle.radius,
                           0, 2 * M_PI,
                           paint, true);
}

void Canvas::draw_circle(Circle &circle) {
    pro_draw_elliptic_arc_(circle.center,
                           circle.radius, circle.radius,
                           0, 2 * M_PI,
                           paint_, true);
}

void Canvas::draw_canvas(Canvas &canvas, Point position, Paint &paint) {
    init_brush(paint);
    cairo_set_source_surface(brush_, canvas.pro_get_cairo_surface(),
                             position.x, position.y);
    cairo_paint(brush_);
    cairo_restore(brush_);
}

void Canvas::draw_canvas(Canvas &canvas, Point position) {
    draw_canvas(canvas, position, paint_);
}

cairo_surface_t *Canvas::pro_get_cairo_surface(void) {
    return surface_;
}

cairo_t *Canvas::pro_get_brush(void) {
    return brush_;
}

void Canvas::clear_all(Paint &paint) {
    cairo_reset_clip(brush_);
    cairo_save(brush_);
    cairo_set_source(brush_, paint.pro_get_background_color_pattern());
    cairo_set_operator(brush_, CAIRO_OPERATOR_SOURCE);
    cairo_paint(brush_);
    cairo_restore(brush_);
}

void Canvas::clear_all(void) {
    clear_all(paint_);
}

void Canvas::clear_viewport(Paint &paint) {
    init_brush(paint);
    cairo_set_source(brush_, paint.pro_get_background_color_pattern());
    cairo_set_operator(brush_, CAIRO_OPERATOR_SOURCE);
    cairo_paint(brush_);
    cairo_restore(brush_);
}

void Canvas::save_PDF_file(const std::string &file_path) {
    std::string file_path_utf8 = yage::util::convert_string(file_path);
    cairo_surface_t *pdf_surface = cairo_pdf_surface_create(file_path_utf8.c_str(), width_, height_);
    cairo_t* pdf_brush = cairo_create(pdf_surface);
    cairo_set_source_surface(pdf_brush, surface_, 0, 0);
    cairo_paint(pdf_brush);
    cairo_destroy(pdf_brush);
    cairo_surface_finish(pdf_surface);
}

void Canvas::save_PNG_file(const std::string &file_path) {
    std::string file_path_utf8 = yage::util::convert_string(file_path);
    cairo_surface_write_to_png(surface_, file_path_utf8.c_str());
}

}  // namespace draw
}  // namespace yage
