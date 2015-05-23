#ifndef DRAW_SHAPE_H_
#define DRAW_SHAPE_H_
#include <vector>
#include "point.h"
#define M_PI 3.14159265358979323846

namespace yage {
namespace draw {

struct EllipticArc {
  Point center;                  ///< Center of the ellipse.
  double xradius, yradius;       ///< X and Y radius of the ellipse.
  double startangle, endangle;   ///< Angles are counterclockwise. Limited to 0 to 2*M_PI.
  EllipticArc() : center(), xradius(0), yradius(0), startangle(0.0), endangle(2 * M_PI) {}
};

struct Circle {
	Point center;
	double radius;
};

struct Ellipse {
    Point center;                  ///< Center of the ellipse.
    double xradius, yradius;       ///< X and Y radius of the ellipse.

    Ellipse(Point center = Point(0, 0),
            double xradius = 0,
            double yradius = 0) : center(center),
                                  xradius(xradius),
                                  yradius(yradius) {}
};

struct Line {
    Point first;
    Point second;
    Line(Point a, Point b): first(a), second(b) {}
};

struct Poly {
    using Vertexes = std::vector<Point>;
    Vertexes vertex;
};

struct Rect {
    Point first;
    Point second;
};

struct EllipticSector: public EllipticArc {
};

}
}
#endif
