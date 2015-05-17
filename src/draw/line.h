#ifndef LINE_H_
#define LINE_H_

#include "shape_property.h"
#include "point.h"

namespace yage {
namespace draw {

class Line : public ShapeProperty {
public:
    Point first;
    Point second;
    Line(Point a, Point b);
};

}
}

#endif // LINE_H_