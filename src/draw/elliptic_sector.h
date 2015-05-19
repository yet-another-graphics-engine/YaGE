#ifndef DRAW_ELLIPTIC_SECTOR_H_
#define DRAW_ELLIPTIC_SECTOR_H_

#include "base_elliptic_arc.h"
#include "shape_property.h"

namespace yage {
namespace draw {

class EllipticSector: public BaseEllipticArc, public ShapeProperty {
public:
    EllipticSector();
};

} // draw
} // yage

#endif //DRAW_ELLIPTIC_ARC_H_
