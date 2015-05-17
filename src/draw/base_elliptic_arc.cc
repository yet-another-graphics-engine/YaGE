#define M_PI 3.14159265358979323846

#include "base_elliptic_arc.h"

namespace yage {
namespace draw {

BaseEllipticArc::BaseEllipticArc() : center(), xradius(0), yradius(0), startangle(0.0), endangle(2 * M_PI) {}

} // draw
} // yage
