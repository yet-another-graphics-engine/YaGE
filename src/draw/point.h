#ifndef POINT_H_3ETAHMDF
#define POINT_H_3ETAHMDF

namespace yage {
namespace draw {

/**
 * A 2D point.
 */
struct Point {
	double x;    ///< x axis of the point.
	double y;    ///< y axis of the point.
	Point(double x = 0, double y = 0);
};

} // namespace draw
} // namespace yage
#endif /* end of include guard: POINT_H_3ETAHMDF */
