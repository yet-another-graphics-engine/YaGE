#ifndef POINT_H_3ETAHMDF
#define POINT_H_3ETAHMDF
#include <istream>
namespace yage {
namespace draw {

/**
 * A 2D point.
 */
class Point {
private:
	double x_;    ///< x axis of the point.
	double y_;    ///< y axis of the point.

public:
	Point();

	Point(double x, double y);

	double getx() const;

	double gety() const;

	void setx(double x);

	void sety(double y);

	friend std::istream &operator>>(std::istream &in, Point &point);
};

} // namespace draw
} // namespace yage
#endif /* end of include guard: POINT_H_3ETAHMDF */
