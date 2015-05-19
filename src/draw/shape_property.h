#ifndef DRAW_SHAPE_PROPERTY_H_
#define DRAW_SHAPE_PROPERTY_H_
#include "color.h"
#include "point.h"

namespace yage {
namespace draw {

/**
 * A base class for all properties of shapes
 */
struct ShapeProperty {
	Color fgcolor;		///< color of the border.
	Color bgcolor;
	double thickness;

	ShapeProperty();
};


} // namespace draw
} // namespace yage
#endif /* end of include guard: DRAW_SHAPE_PROPERTY_H_ */
