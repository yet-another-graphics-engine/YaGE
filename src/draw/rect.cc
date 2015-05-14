#include "rect.h"
#include <algorithm>

namespace yage {
namespace draw {

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
}

/**
 * Initialize a rectangle with given name
 * @param name the name of the shape
 */
Rect::Rect(std::string name)
		: ShapeProperty(name, "rectangle")
{
}

} // namespace draw
} // namespace yage
