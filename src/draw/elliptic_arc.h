#ifndef DRAW_ELLIPTIC_ARC_H_
#define DRAW_ELLIPTIC_ARC_H_

#include "base_elliptic_arc.h"
#include "shape_property.h"

namespace yage {
namespace draw {

class EllipticArc: public BaseEllipticArc, public ShapeProperty {
public:
    EllipticArc();
};

} // draw
} // yage

#endif //DRAW_ELLIPTIC_ARC_H_
