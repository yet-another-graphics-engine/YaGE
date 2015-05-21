#include "canvas.h"
#define M_PI 3.14159265358979323846
#ifdef _WIN32
#include "../util/mswin.h"
#include <cstdlib>
#endif

using namespace yage::draw;

namespace yage {
namespace draw {


Canvas::Canvas(int width, int height,Color bg_color) {
    width_=width;
    height_=height;
    bg_color_=bg_color;
    viewport_left_top_.x=viewport_left_top_.y=0;
    viewport_right_bottom_.x=width-1;
    viewport_right_bottom_.y=height-1;

    buffer_surface_ = nullptr;
    buffer_brush_ = nullptr;
    surface_ = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    brush_ = cairo_create(surface_);
    clear_all();
}

Canvas::Canvas(std::string filename,Color bg_color) {
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

    bg_color_=bg_color;
    viewport_left_top_.x=viewport_left_top_.y=0;
    viewport_right_bottom_.x=width_-1;
    viewport_right_bottom_.y=height_-1;
    buffer_surface_ = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width_, height_);
    buffer_brush_ = cairo_create(buffer_surface_);
}

Canvas::~Canvas() {
    if(buffer_surface_!=nullptr)
    {
        cairo_destroy(buffer_brush_);
        cairo_surface_destroy(buffer_surface_);
    }
    cairo_destroy(brush_);
    cairo_surface_destroy(surface_);
}


void Canvas::update_canvas(void)  {
    //g_print("canvas_update.\n");
    if(buffer_surface_!=nullptr)
    {
        cairo_save(brush_);
        cairo_set_line_width(brush_,0);
        cairo_rectangle(brush_,viewport_left_top_.x,
                               viewport_left_top_.y,
                               viewport_right_bottom_.x-viewport_left_top_.x+1,
                               viewport_right_bottom_.y-viewport_left_top_.y+1);
        cairo_set_source_surface(brush_,buffer_surface_,viewport_left_top_.x,
                                                        viewport_left_top_.y);
        cairo_fill(brush_);
        cairo_restore(brush_);

        cairo_destroy(buffer_brush_);
        cairo_surface_destroy(buffer_surface_);
    }

    buffer_surface_ = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width_, height_);
    buffer_brush_ = cairo_create(buffer_surface_);
}

void Canvas::shape_fill_and_stroke_(ShapeProperty &shape) {
    cairo_scale(buffer_brush_, 1.0, 1.0);
    cairo_set_source_rgba(buffer_brush_,
                          shape.bgcolor.r,
                          shape.bgcolor.g,
                          shape.bgcolor.b,
                          shape.bgcolor.a);
    cairo_fill_preserve(buffer_brush_);
    shape_stroke_(shape);
}

void Canvas::shape_stroke_(ShapeProperty &shape) {
    cairo_scale(buffer_brush_, 1.0, 1.0);
    cairo_set_source_rgba(buffer_brush_,
                          shape.fgcolor.r,
                          shape.fgcolor.g,
                          shape.fgcolor.b,
                          shape.fgcolor.a);
    cairo_stroke(buffer_brush_);
}

void Canvas::draw_line(Line &line) {
    cairo_save(buffer_brush_);
    cairo_set_line_width(buffer_brush_,line.thickness);
    cairo_move_to(buffer_brush_, line.first.x, line.first.y);
    cairo_line_to(buffer_brush_, line.second.x, line.second.y);
    shape_stroke_(line);
    cairo_restore(buffer_brush_);
}

void Canvas::pro_draw_elliptic_arc_(Point center, double xradius, double yradius, double startangle, double endangle, ShapeProperty &shape, bool draw_sector)  {
    // Drawing Elliptic Arc procedure
    // Finally, we will draw a arc with radius of 0 at (0,0)
    cairo_save(buffer_brush_);
    cairo_set_line_width(buffer_brush_, shape.thickness);
    cairo_translate(buffer_brush_, center.x, center.y); // make center of ellipse arc (0,0)

    cairo_save(buffer_brush_);
    cairo_scale(buffer_brush_, xradius, yradius);  // scale ellipse to a circle having radius of 1
    cairo_arc(buffer_brush_, 0.0, 0.0, 1.0, startangle, endangle); // draw the 'circle arc'
    if (draw_sector) {
        cairo_line_to(buffer_brush_, 0, 0);
        cairo_close_path(buffer_brush_);
    }

    cairo_restore(buffer_brush_);
    if (draw_sector) {
        shape_fill_and_stroke_(shape);
    } else {
        shape_stroke_(shape);
    }
    cairo_restore(buffer_brush_);
}

void Canvas::draw_text(Text &text) {
    cairo_save(buffer_brush_);
    PangoLayout *layout = pango_cairo_create_layout(buffer_brush_);
#ifdef _WIN32
    char *utf_text = yage::util::ansi_to_utf_8(text.text.c_str());
#else
    const char *utf_text = text.text.c_str();
#endif
    pango_layout_set_text(layout, utf_text, -1);
    pango_layout_set_font_description(layout, text.get_font().pro_get_pango_font());
    cairo_translate(buffer_brush_, text.position.x, text.position.y);
    cairo_set_source_rgba(buffer_brush_,
                          text.color.r,
                          text.color.g,
                          text.color.b,
                          text.color.a);
    pango_cairo_show_layout(buffer_brush_, layout);
#ifdef _WIN32
    free(utf_text);
#endif
    g_object_unref(layout);
    cairo_restore(buffer_brush_);
    //update_canvas();
}

void Canvas::draw_poly(Poly &poly) {
    cairo_save(buffer_brush_);
    cairo_set_line_width(buffer_brush_, poly.thickness);
    for (const auto &i : poly.vertex) {
        cairo_line_to(buffer_brush_, i.x, i.y);
    }
    cairo_close_path(buffer_brush_);
    shape_fill_and_stroke_(poly);
    cairo_restore(buffer_brush_);
}

void Canvas::draw_rect(Rect &rect)  {
    cairo_save(buffer_brush_);
    const Point &a = rect.first;
    const Point &b = rect.second;
    cairo_rectangle(buffer_brush_, a.x, a.y, b.x - a.x, b.y - a.y);
    shape_fill_and_stroke_(rect);
    cairo_restore(buffer_brush_);
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
    cairo_save(buffer_brush_);
    cairo_set_source_surface(buffer_brush_, canvas.pro_get_cairo_surface(), position.x, position.y);
    cairo_paint(buffer_brush_);
    cairo_restore(buffer_brush_);
}

Color Canvas::get_bg_color()
{
    return bg_color_;
}

void Canvas::set_bg_color(Color color)
{
    bg_color_=color;
}

void Canvas::set_viewport(Point left_top,Point right_bottom)
{
    update_canvas();
    viewport_left_top_.x=(left_top.x < right_bottom.x)?left_top.x:right_bottom.x;
    viewport_right_bottom_.x=(left_top.x > right_bottom.x)?left_top.x:right_bottom.x;
    viewport_left_top_.y=(left_top.y < right_bottom.y)?left_top.y:right_bottom.y;
    viewport_right_bottom_.y=(left_top.y > right_bottom.y)?left_top.y:right_bottom.y;

    viewport_right_bottom_.x--;
    viewport_right_bottom_.y--;
    if(viewport_left_top_.x<0)
        viewport_left_top_.x=0;
    else if(viewport_left_top_.x>=width_)
        viewport_left_top_.x=width_-1;

    if(viewport_left_top_.y<0)
        viewport_left_top_.y=0;
    else if(viewport_left_top_.y>=height_)
        viewport_left_top_.y=height_-1;

    if(viewport_right_bottom_.x<0)
        viewport_right_bottom_.x=0;
    else if(viewport_right_bottom_.x>=width_)
        viewport_right_bottom_.x=width_-1;

    if(viewport_right_bottom_.y<0)
        viewport_right_bottom_.y=0;
    else if(viewport_right_bottom_.y>=height_)
        viewport_right_bottom_.y=height_-1;
}

void Canvas::get_viewport(Point* left_top,Point* right_bottom)
{
    *left_top=viewport_left_top_;
    *right_bottom=viewport_right_bottom_;
}

cairo_surface_t *Canvas::pro_get_cairo_surface(void)  {
    return surface_;
}

cairo_t *Canvas::pro_get_brush(void)  {
    return brush_;
}

void Canvas::clear_all(void) {
    update_canvas();
    cairo_save(brush_);
    cairo_set_source_rgba(brush_,bg_color_.r,
                                 bg_color_.g,
                                 bg_color_.b,
                                 bg_color_.a);
    cairo_paint(brush_);
    cairo_restore(brush_);
}

void Canvas::clear_viewport(void){
    update_canvas();
    cairo_save(brush_);
    cairo_set_line_width(brush_,0);
    cairo_set_source_rgba(brush_,bg_color_.r,
                                 bg_color_.g,
                                 bg_color_.b,
                                 bg_color_.a);
    cairo_rectangle(brush_,viewport_left_top_.x,
                           viewport_left_top_.y,
                           viewport_right_bottom_.x-viewport_left_top_.x+1,
                           viewport_right_bottom_.y-viewport_left_top_.y+1);
    cairo_fill(brush_);
    cairo_restore(brush_);
}

}
}
