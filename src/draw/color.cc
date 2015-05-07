#include "color.h"

namespace yage {
namespace draw {


/*
 * Set the color by RGB and alpha channel.
 * @param a Alpha of the color; 0 for transparent and 1 for full color
 */
Color::Color(double r, double g, double b, double a)
        : r_(r), g_(g), b_(b), a_(a)
{
}

Color::Color()
        : Color(0, 0, 0)
{
}

/**
 * Get red channel
 * @return a number between 0 and 1
 */
double Color::getr() const
{
    return r_;
}

/**
 * Get green channel
 * @return a number between 0 and 1
 */
double Color::getg() const
{
    return g_;
}

/**
 * Get blue channel
 * @return a number between 0 and 1
 */
double Color::getb() const
{
    return b_;
}

/**
 * Get alpha channel
 * @return a number between 0 and 1
 */
double Color::geta() const
{
    return a_;
}


} // namespace draw
} // namespace yage
