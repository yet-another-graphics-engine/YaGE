#define M_PI 3.14159265358979323846
#include "base_elliptic_arc.h"

namespace yage {
namespace draw {

BaseEllipticArc::BaseEllipticArc() : center_(), xradius_(0), yradius_(0), startangle_(0.0), endangle_(2 * M_PI){ }

Point &BaseEllipticArc::get_center()  {
    return center_;
}

double BaseEllipticArc::get_xradius()  {
    return xradius_;
}

double BaseEllipticArc::get_yradius()  {
    return yradius_;
}

double BaseEllipticArc::get_startangle()  {
    return startangle_;
}

double BaseEllipticArc::get_endangle()  {
    return endangle_;
}

void BaseEllipticArc::set_center(Point &center) {
    center_ = center;
}

void BaseEllipticArc::set_xradius(double radius) {
    xradius_ = radius;
}

void BaseEllipticArc::set_yradius(double radius) {
    yradius_ = radius;
}

void BaseEllipticArc::set_startangle(double angle) {
    startangle_ = angle;
}

void BaseEllipticArc::set_endangle(double angle) {
    endangle_ = angle;
}

} // draw
} // yage
