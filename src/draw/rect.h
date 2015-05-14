#ifndef RECT_H_LWYTDFQS
#define RECT_H_LWYTDFQS
#include "shape_property.h"
#include "base_poly.h"

namespace yage {
namespace draw {

class Rect : public ShapeProperty {
	private:
		Point a_, b_;	///< Two diagonal points on the rectangle.

	public:
		using PointSet = std::pair<Point, Point>;
		PointSet get_points() const;
		void set_points(const Point &a, const Point &b);
		Rect(std::string name = "");
};


} // namespace draw
} // namespace yage
#endif /* end of include guard: RECT_H_LWYTDFQS */
