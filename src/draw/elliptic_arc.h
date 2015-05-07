#ifndef ELLIPTIC_ARC_H_
#define ELLIPTIC_ARC_H_
#include "basic_shape.h"

namespace yage {
namespace draw {

class EllipticArc : public BasicShape {
	private:
		Point center_;                  ///< Center of the ellipse.
		double xradius_, yradius_;      ///< X and Y radius of the ellipse.
		double startangle_, endangle_;  ///< Angles are counterclockwise. Limited to 0 to 2*M_PI.

	public:
		EllipticArc(std::string name = "");
		
		Point& get_center() ;
		double get_xradius() ;
		double get_yradius() ;
		double get_startangle() ;
		double get_endangle() ;

		void set_center( Point &center);
		void set_xradius(double radius);
		void set_yradius(double radius);
		void set_startangle(double angle);
		void set_endangle(double angle);
};

}
}
#endif
