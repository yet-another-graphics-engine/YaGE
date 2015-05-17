#ifndef ELLIPTIC_ARC_H
#define ELLIPTIC_ARC_H

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

#endif //ELLIPTIC_ARC_H
