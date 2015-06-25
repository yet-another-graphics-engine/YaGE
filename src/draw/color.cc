#include "color.h"

namespace yage {
namespace draw {


/**
 * Set the color by RGB and alpha channel.
 * @param a Alpha of the color; 0 for transparent and 1 for full color
 */
Color::Color(double r, double g, double b, double a): r(r), g(g), b(b), a(a) {}

Color::Color(unsigned int ege_color) {
    r = 1.0 * ((ege_color >> 16) & 0xFF) / 0xFF;
    g = 1.0 * ((ege_color >> 8) & 0xFF) / 0xFF;
    b = 1.0 * ((ege_color) & 0xFF) / 0xFF;
    a = 1.0;
}

} // namespace draw
} // namespace yage
