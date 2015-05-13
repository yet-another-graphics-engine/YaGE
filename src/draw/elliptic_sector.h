#ifndef ELLIPTIC_SECTOR_H
#define ELLIPTIC_SECTOR_H

#include "base_elliptic_arc.h"
#include "shape_property.h"

namespace yage {
namespace draw {

class EllipticSector: public BaseEllipticArc, public ShapeProperty {
public:
    EllipticSector(std::string name = "");
};

} // draw
} // yage

#endif //ELLIPTIC_ARC_H
