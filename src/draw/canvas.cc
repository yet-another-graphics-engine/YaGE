#include "canvas.h"

namespace yage {
namespace draw {

Canvas::Canvas(Window &window) : ShapeProperty("", "canvas") , window_(&window) {
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

Canvas::Canvas(int width, int height) : ShapeProperty("", "canvas") {
    surface_ = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    brush_ = cairo_create(surface_);
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
    // if (window_) window_->pro_redraw();
}

void Canvas::shape_fill_(ShapeProperty &shape)  {
    cairo_set_source_rgba(brush_,
                          shape.get_fgcolor().getr(),
                          shape.get_fgcolor().getg(),
                          shape.get_fgcolor().getb(),
                          shape.get_fgcolor().geta());
    cairo_fill_preserve(brush_);

    cairo_scale(brush_, 1.0, 1.0);

    cairo_set_source_rgba(brush_,
                          shape.get_bgcolor().getr(),
                          shape.get_bgcolor().getg(),
                          shape.get_bgcolor().getb(),
                          shape.get_bgcolor().geta());
    cairo_stroke(brush_);
}

// dirty hack for wrong class model
void Canvas::pro_draw_elliptic_arc_(BaseEllipticArc &elliparc, ShapeProperty &shape)  {
    // Drawing Elliptic Arc procedure
    // Finally, we will draw a arc with radius of 0 at (0,0)
    init_brush_();
    cairo_set_line_width(brush_, shape.get_thickness());
    cairo_translate(brush_, elliparc.get_center().getx(), elliparc.get_center().gety()); // make center of ellipse arc (0,0)
    init_brush_();
    cairo_scale(brush_, elliparc.get_xradius(), elliparc.get_yradius());  // scale ellipse to a circle having radius of 1
    cairo_arc(brush_, 0.0, 0.0, 1.0, elliparc.get_startangle(), elliparc.get_endangle()); // draw the 'circle arc'
    finish_brush_();
    shape_fill_(shape);
    finish_brush_();
}

void Canvas::pro_draw_ellipse_(BaseEllipse &ellipse, ShapeProperty &shape)  {
    pro_draw_elliptic_arc_(ellipse.pro_get_base_elliptic_arc(), shape);
}

// dirty hack for wrong class model
void Canvas::pro_draw_poly_(BasePoly &poly, ShapeProperty &shape)  {
    init_brush_();
    cairo_set_line_width(brush_, shape.get_thickness());
    for (const auto &i : poly.vertex) {
        cairo_line_to(brush_, i.getx(), i.gety());
    }
    cairo_close_path(brush_);
    shape_fill_(shape);
    finish_brush_();
}

void Canvas::draw_picture(Picture &picture)  {

}

void Canvas::draw_text(Text &text) {

}

void Canvas::draw_poly(Poly &poly) {
    pro_draw_poly_(poly, poly);
}

void Canvas::draw_rect(Rect &rect)  {
    pro_draw_poly_(rect.pro_get_base_poly(), rect);
}

void Canvas::draw_elliptical_arc(EllipticArc &ellparc) {
    pro_draw_elliptic_arc_(ellparc, ellparc);
}

void Canvas::draw_ellipse(Ellipse &ellipse) {
    pro_draw_ellipse_(ellipse, ellipse);
}

void Canvas::draw_circle(Circle &circle)  {
    pro_draw_ellipse_(circle.pro_get_base_ellipse(), circle);
}

cairo_surface_t *Canvas::pro_get_cairo_surface()  {
    return surface_;
}

cairo_t *Canvas::pro_get_brush()  {
    return brush_;
}

}
}
