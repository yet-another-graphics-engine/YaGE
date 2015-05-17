#ifndef POLY_H
#define POLY_H
#include "shape_property.h"
#include <vector>

namespace yage {
namespace draw {

struct Poly : public ShapeProperty {
public:
    using Vertexes = std::vector<Point>; ///< Type for the container of all vertexes
    Vertexes vertex;	///< All vertexes
    Poly();
};

} // namespace draw
} // namespace yage


#endif //POLY_H
