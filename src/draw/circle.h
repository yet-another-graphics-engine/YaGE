#ifndef CIRCLE_H_
#define CIRCLE_H_
#include "shape_property.h"
#include "base_ellipse.h"

namespace yage {
namespace draw {

class Circle : public ShapeProperty {
	private:
		BaseEllipse ellipse_;
	public:
        Circle(std::string name = "");

		Point get_center() ;
		double get_radius() ;

		void set_center(Point &center);
        void set_radius(double radius);

        BaseEllipse &pro_get_base_ellipse(void);
};

}
}

#endif
