#include "point.h"

namespace yage {
namespace draw {

/**
 * Initialize a point at (0, 0)
 */
Point::Point()
{
    x_ = y_ = 0;
}

/**
 * Initialize a point at given position.
 * @param x x axis of the position
 * @param y y axis of the position
 */
Point::Point(double x, double y)
        : x_(x), y_(y)
{
}

/**
 * Get the x axis of the point
 * @return the position
 */
double Point::getx() const
{
    return x_;
}

/**
 * Get the y axis of the point
 * @return the position
 */
double Point::gety() const
{
    return y_;
}

/**
 * Set the x axis of the point
 * @param x the position
 */
void Point::setx(double x)
{
    x_ = x;
}

/**
 * Set the y axis of the point
 * @param y the position
 */
void Point::sety(double y)
{
    y_ = y;
}


std::istream& operator>>(std::istream &in, Point &point)
{
    in >> point.x_;
    in >> point.y_;
    return in;
}

} // namespace draw
} // namespace yage