#ifndef DRAW_CANVAS_H_
#define DRAW_CANVAS_H_

#include "text.h"
#include "color.h"
#include "paint.h"
#include "shape.h"
#include "animation.h"

#include <cairo.h>
#include <cairo-pdf.h>
#include <pango/pango.h>
#include <gdk/gdk.h>
#include <vector>

using namespace yage::draw;

namespace yage {
namespace draw {

/**
 * @brief yage::draw::Canvas is the carrier of graphics.
 * All the kinds of graphics,including lines,rectangles,circles,texts,pictures and so on,
 * should be drawn on a canvas in a YaGE program.A canvas can also be set for a window to be used
 * to update the window's interface.
 */
class Canvas {
    private:
        cairo_surface_t *surface_;
        cairo_t *brush_;

        Paint paint_;
        int width_;
        int height_;

        void init_brush(Paint &paint);
        void shape_fill_and_stroke_(Paint &paint);
        void shape_stroke_(Paint &paint);
        void pro_draw_elliptic_arc_(Point center, double xradius, double yradius, double startangle, double endangle,
                                    Paint &paint, bool draw_sector = false);
    public:
        /**
         * @brief Creates a blank canvas.
         * @param width The width of the new canvas.
         * @param height The height of the new canvas.
         */
        Canvas(int width, int height);

        /**
         * @brief Creates a canvas from a specific picture file.
         * @param filename The path of the specific picture file.
         * @note The supportive image types include JPEG,BMP,PNG and so on.
         */
        Canvas(const std::string &filename);

        /**
         * @brief Copies the content of the another canvas to this canvas.
         * @param canvas The canvas which is to be copied.
         */
        Canvas(Canvas& canvas);
        ~Canvas();

        /**
         * @brief Gets the size of the canvas.
         * @param [out]width The width value of the canvas will be written here.
         * @param [out]height The height value of the canvas will be written here.
         */
        void get_size(int &width,int &height);

        /**
         * @brief Draws a line on the canvas with a specific paint.
         * @param line Indicates the region where the line will be drawn.
         * @param paint The paint used to draw this line.
         */
        void draw_line(Line &line,Paint &paint);

        /**
         * @brief Draws a line on the canvas with the default paint.
         * @param line Indicates the region where the line will be drawn.
         */
        void draw_line(Line &line);

        /**
         * @brief Draws a polygon on the canvas with a specific paint.
         * @param poly Indicates the region where the polygon will be drawn.
         * @param paint The paint used to draw this polygon.
         */
        void draw_poly(Poly &poly, Paint &paint);

        /**
         * @brief Draws a polygon on the canvas with the default paint.
         * @param poly Indicates the region where the polygon will be drawn.
         */
        void draw_poly(Poly &poly);

        /**
         * @brief Draws a rectangle on the canvas with a specific paint.
         * @param rect Indicates the region where the rectangle will be drawn.
         * @param paint The paint used to draw this rectangle.
         */
        void draw_rect(Rect &rect, Paint &paint);

        /**
         * @brief Draws a rectangle on the canvas with the default paint.
         * @param rect Indicates the region where the rectangle will be drawn.
         */
        void draw_rect(Rect &rect);

        /**
         * @brief Draws an arc on the canvas with a specific paint.
         * @param elliparc Indicates the region where the arc will be drawn.
         * @param paint The paint used to draw this arc.
         */
        void draw_elliptical_arc(EllipticArc &elliparc, Paint &paint);

        /**
         * @brief Draws an arc on the canvas with the default paint.
         * @param elliparc Indicates the region where the arc will be drawn.
         */
        void draw_elliptical_arc(EllipticArc &elliparc);

        /**
         * @brief Draws a sector on the canvas with a specific paint.
         * @param ellipsec Indicates the region where the sector will be drawn.
         * @param paint The paint used to draw this sector.
         */
        void draw_elliptical_sector(EllipticSector &ellipsec, Paint &paint);

        /**
         * @brief Draws a sector on the canvas with the default paint.
         * @param ellipsec Indicates the region where the sector will be drawn.
         */
        void draw_elliptical_sector(EllipticSector &ellipsec);

        /**
         * @brief Draws an ellipse on the canvas with a specific paint.
         * @param ellipse Indicates the region where the ellipse will be drawn.
         * @param paint The paint used to draw this ellipse.
         */
        void draw_ellipse(Ellipse &ellipse, Paint &paint);

        /**
         * @brief Draws an ellipse on the canvas with the default paint.
         * @param ellipse Indicates the region where the ellipse will be drawn.
         */
        void draw_ellipse(Ellipse &ellipse);

        /**
         * @brief Draws a circle on the canvas with a specific paint.
         * @param circle Indicates the region where the circle will be drawn.
         * @param paint The paint used to draw this circle.
         */
        void draw_circle(Circle &circle, Paint &paint);

        /**
         * @brief Draws a circle on the canvas with the default paint.
         * @param circle Indicates the region where the circle will be drawn.
         */
        void draw_circle(Circle &circle);

        /**
         * @brief Draws a text on the canvas with a specific paint.
         * @param text Indicates the region where the text will be drawn.
         * @param paint The paint used to draw this text.
         * @note The color of the text is according to Paint::font_color.
         * @note The size info of the text is in Paint::font.
         * @see Font
         */
        void draw_text(Text &text, Paint &paint);

        /**
         * @brief Draws a text on the canvas with the default paint.
         * @param text Indicates the region where the text will be drawn.
         * @note The color of the text is according to Paint::font_color.
         * @note The size info of the text is in Paint::font.
         * @see Font
         */
        void draw_text(Text &text);

        /**
         * @brief Draws the content of an another canvas on this canvas with a specific paint.
         * @param canvas The another canvas used to be drawn on this canvas.
         * @param position The start(left-top) position in this canvas.Drawing will start from
         * this position.
         * @param paint The paint used to draw the content of the another canvas.
         */
        void draw_canvas(Canvas &canvas, Point position, Paint &paint);

        /**
         * @brief Draws the content of an another canvas on this canvas with the default paint.
         * @param canvas The another canvas used to be drawn on this canvas.
         * @param position The start(left-top) position in this canvas.Drawing will start from
         * this position.
         */
        void draw_canvas(Canvas &canvas, Point position);

        /**
         * @brief Clear all the content of this canvas by filling the whole canvas with
         * a specific paint.
         * @param paint The paint used to clear this canvas.
         * @note The color used to fill this canvas is according to Paint::background_color.
         */
        void clear_all(Paint &paint);

        /**
         * @brief Clear all the content of this canvas by filling the whole canvas with
         * the default paint.
         * @note The color used to fill this canvas is according to Paint::background_color.
         */
        void clear_all(void);

        /**
         * @brief Clear all the content of the viewport in this canvas by filling the whole
         * viewport with a specific paint.
         * @param paint The paint used to clear the viewport.
         * @note The viewport info is in the paint.You can use the function Paint::set_viewport to set the viewport.
         * @note The color used to fill the viewport is according to Paint::background_color.
         */
        void clear_viewport( Paint &paint);

        /**
         * @brief Save the content of this canvas to a PDF file.
         * @param file_path The PDF file's path.
         */
        void save_PDF_file(const std::string &file_path);

        /**
         * @brief Save the content of this canvas to a PNG file.
         * @param file_path The PNG file's path.
         */
        void save_PNG_file(const std::string &file_path);

        /**
         * @brief (Pro)Gets the pointer of the Cairo Surface in the canvas object.
         * @return The pointer of the Cairo Surface.
         */
        cairo_surface_t *pro_get_cairo_surface(void);

        /**
         * @brief (Pro)Gets the pointer of the Cairo Context in the canvas object.
         * @return The pointer of the Cairo Context.
         */
        cairo_t *pro_get_brush(void);
};

}
}
#endif
