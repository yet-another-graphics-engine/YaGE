#ifndef BASE_ELLIPSE_H_
#define BASE_ELLIPSE_H_
#include "shape_property.h"
#include "base_elliptic_arc.h"

namespace yage {
namespace draw {

class BaseEllipse {
    private:
        BaseEllipticArc elliparc_;
    public:
        Point get_center() ;
        double get_xradius() ;
        double get_yradius() ;

        void set_center(Point &center);
        void set_xradius(double radius);
        void set_yradius(double radius);

        BaseEllipticArc &pro_get_base_elliptic_arc(void);
};


}
}


#endif
