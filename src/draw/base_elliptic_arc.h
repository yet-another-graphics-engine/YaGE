#ifndef DRAW_BASE_ELLIPTIC_ARC_H_
#define DRAW_BASE_ELLIPTIC_ARC_H_

#include "point.h"

namespace yage {
namespace draw {

struct BaseEllipticArc {
public:
	Point center;                  ///< Center of the ellipse.
	double xradius, yradius;       ///< X and Y radius of the ellipse.
	double startangle, endangle;   ///< Angles are counterclockwise. Limited to 0 to 2*M_PI.

	BaseEllipticArc();
};

} // draw
} // yage
#endif
