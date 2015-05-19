#ifndef DRAW_RECT_H_
#define DRAW_RECT_H_
#include "shape_property.h"

namespace yage {
namespace draw {

class Rect : public ShapeProperty {
public:
    Point first;
    Point second;
    Rect();
};


} // namespace draw
} // namespace yage
#endif /* end of include guard: DRAW_RECT_H_ */
