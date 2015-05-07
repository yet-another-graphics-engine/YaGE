#include "ellipse.h"
#include "point.h"

namespace yage {
namespace draw {

Ellipse::Ellipse(std::string name) : BasicShape(name, "ellipse"), elliparc_(name) { }

Point Ellipse::get_center()  {
    return elliparc_.get_center();
}

double Ellipse::get_xradius()  {
    return elliparc_.get_xradius();
}

double Ellipse::get_yradius()  {
    return elliparc_.get_yradius();
}

void Ellipse::set_center( Point &center) {
    elliparc_.set_center(center);
}

void Ellipse::set_xradius(double radius) {
    elliparc_.set_xradius(radius);
}

void Ellipse::set_yradius(double radius) {
    elliparc_.set_yradius(radius);
}

EllipticArc &Ellipse::pro_get_elliptic_arc(void) {
    return elliparc_;
}

}
}