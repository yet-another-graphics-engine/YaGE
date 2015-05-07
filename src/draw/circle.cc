#include "circle.h"
#include "point.h"
#include "ellipse.h"

namespace yage {
namespace draw {
Circle::Circle(std::string name) : BasicShape(name, "circle"), ellipse_(name) { }

Point Circle::get_center()  {
    return ellipse_.get_center();
}

double Circle::get_radius()  {
    return ellipse_.get_xradius();
}

void Circle::set_center( Point &center) {
    ellipse_.set_center(center);
}

void Circle::set_radius(double radius) {
    ellipse_.set_xradius(radius);
    ellipse_.set_yradius(radius);
}

Ellipse &Circle::pro_get_ellipse(void) {
    return ellipse_;
}

}
}