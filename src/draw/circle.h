#ifndef CIRCLE_H_
#define CIRCLE_H_
#include "shape_property.h"

namespace yage {
namespace draw {

struct Circle : public ShapeProperty {
	Point center;
	double radius;
	Circle();
};

}
}

#endif
