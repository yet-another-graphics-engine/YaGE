#ifndef LINE_H_
#define LINE_H_

#include "shape_property.h"
#include "point.h"

namespace yage {
namespace draw {

class Line : public ShapeProperty {
public:
    Line(std::string name);
    void set_points(Point start, Point end);
    std::pair<Point, Point> get_points(void);

private:
    std::pair<Point, Point> points_;
};

}
}

#endif // LINE_H_