#include "line.h"

namespace yage {
namespace draw {

Line::Line(std::string name) : ShapeProperty(name, "line") {}

void Line::set_points(Point start, Point end) {
    points_.first = start;
    points_.second = end;
}

std::pair<Point, Point> Line::get_points(void) {
    return points_;
}


}
}