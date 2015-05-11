#ifndef POLY_H
#define POLY_H
#include "base_poly.h"

namespace yage {
namespace draw {

class Poly : public BasePoly, public ShapeProperty {
public:
    Poly(std::string name="");
};

} // namespace draw
} // namespace yage


#endif //POLY_H
