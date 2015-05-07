#ifndef CIRCLE_H_
#define CIRCLE_H_
#include "basic_shape.h"
#include "ellipse.h"

namespace yage {
namespace draw {

class Circle : public BasicShape {
	private:
		Ellipse ellipse_;
	public:
        Circle(std::string name = "");

		Point get_center() ;
		double get_radius() ;

		void set_center(Point &center);
        void set_radius(double radius);

        Ellipse &pro_get_ellipse(void);
};

}
}

#endif
