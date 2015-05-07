#include <cmath>
#include "elliptic_arc.h"

namespace yage {
namespace draw {
EllipticArc::EllipticArc(std::string name) : BasicShape(name, "elliptic_arc"), xradius_(0), yradius_(0), startangle_(0),
                                             endangle_(2 * M_PI) { }

Point &EllipticArc::get_center()  {
    return center_;
}

double EllipticArc::get_xradius()  {
    return xradius_;
}

double EllipticArc::get_yradius()  {
    return yradius_;
}

double EllipticArc::get_startangle()  {
    return startangle_;
}

double EllipticArc::get_endangle()  {
    return endangle_;
}

void EllipticArc::set_center( Point &center) {
    center_ = center;
}

void EllipticArc::set_xradius(double radius) {
    xradius_ = radius;
}

void EllipticArc::set_yradius(double radius) {
    yradius_ = radius;
}

void EllipticArc::set_startangle(double angle) {
    startangle_ = angle;
}

void EllipticArc::set_endangle(double angle) {
    endangle_ = angle;
}

}
}