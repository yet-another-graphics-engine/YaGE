#include "rect.h"
#include <algorithm>

namespace yage {
namespace draw {

/**
 * Rebuild the polygen according to two diagonal points;
 */
void Rect::rebuild_poly()
{
	auto x = std::minmax<double>(a_.getx(), b_.getx());
	auto y = std::minmax<double>(a_.gety(), b_.gety());
	poly_.vertex = Poly::Vertexes{
		Point(x.first,	y.first),
		Point(x.second,	y.first),
		Point(x.second,	y.second),
		Point(x.first,	y.second)};
}


/**
 * Get the diagonal points of the rectangle.
 * @return two points representing the rectangle
 */
Rect::PointSet Rect::get_points() const
{
	return Rect::PointSet(a_, b_);
}

/**
 * Set the diagonal points of the rectangle.
 * @param points a set of two points representing the rectangle
 */
void Rect::set_points(const Point &a, const Point &b)
{
	a_ = a;
	b_ = b;
	rebuild_poly();
}

/**
 * Initialize a rectangle with given name
 * @param name the name of the shape
 */
Rect::Rect(std::string name)
		: BasicShape(name, "rectangle")
{
}

Poly &Rect::pro_get_poly(void) {
    return poly_;
}

} // namespace draw
} // namespace yage
