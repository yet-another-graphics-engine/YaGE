#ifndef RECT_H_LWYTDFQS
#define RECT_H_LWYTDFQS
#include "basic_shape.h"
#include "poly.h"

namespace yage {
namespace draw {

class Rect : public BasicShape {
	private:
		Poly poly_;	///< Internal polygon.
		Point a_, b_;	///< Two diagonal points on the rectangle.
		void rebuild_poly();

	public:
		using PointSet = std::pair<Point, Point>;
		PointSet get_points() const;
		void set_points(const Point &a, const Point &b);
		Rect(std::string name = "");

        Poly &pro_get_poly(void);
};


} // namespace draw
} // namespace yage
#endif /* end of include guard: RECT_H_LWYTDFQS */
