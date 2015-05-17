#ifndef RECT_H_LWYTDFQS
#define RECT_H_LWYTDFQS
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
#endif /* end of include guard: RECT_H_LWYTDFQS */
