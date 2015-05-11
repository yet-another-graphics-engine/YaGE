#include "base_ellipse.h"
#include "point.h"

namespace yage {
namespace draw {

Point BaseEllipse::get_center()  {
    return elliparc_.get_center();
}

double BaseEllipse::get_xradius()  {
    return elliparc_.get_xradius();
}

double BaseEllipse::get_yradius()  {
    return elliparc_.get_yradius();
}

void BaseEllipse::set_center(Point &center) {
    elliparc_.set_center(center);
}

void BaseEllipse::set_xradius(double radius) {
    elliparc_.set_xradius(radius);
}

void BaseEllipse::set_yradius(double radius) {
    elliparc_.set_yradius(radius);
}

BaseEllipticArc &BaseEllipse::pro_get_base_elliptic_arc(void) {
    return elliparc_;
}

}
}