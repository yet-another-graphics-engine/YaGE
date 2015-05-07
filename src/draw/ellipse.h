#ifndef ELLIPSE_H_
#define ELLIPSE_H_
#include "basic_shape.h"
#include "elliptic_arc.h"

namespace yage {
namespace draw {

class Ellipse : public BasicShape {
    private:
        EllipticArc elliparc_;
    public:
        Ellipse(std::string name = "");

        Point get_center() ;
        double get_xradius() ;
        double get_yradius() ;

        void set_center( Point &center);
        void set_xradius(double radius);
        void set_yradius(double radius);

        EllipticArc &pro_get_elliptic_arc(void);
};


}
}


#endif
