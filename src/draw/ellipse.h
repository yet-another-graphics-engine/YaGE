#include "shape_property.h"

#ifndef ELLIPSE_H
#define ELLIPSE_H

namespace yage {
namespace draw {

struct Ellipse : public ShapeProperty {
public:
    Point center;                  ///< Center of the ellipse.
    double xradius, yradius;       ///< X and Y radius of the ellipse.
    Ellipse(Point center=Point(0,0), double xradius=0.0, double yradius=0.0);
};

} // namespace draw
} // namespace yage


#endif //ELLIPSE_H
