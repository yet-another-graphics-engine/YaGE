#ifndef SHAPE_PROPERTY_H_JZUADHOK
#define SHAPE_PROPERTY_H_JZUADHOK
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
#endif /* end of include guard: SHAPE_PROPERTY_H_JZUADHOK */
