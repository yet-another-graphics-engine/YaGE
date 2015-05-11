#include "base_ellipse.h"

#ifndef ELLIPSE_H
#define ELLIPSE_H

namespace yage {
namespace draw {

class Ellipse : public BaseEllipse, public ShapeProperty {
public:
    Ellipse(std::string name);
};

} // namespace draw
} // namespace yage


#endif //ELLIPSE_H
