#ifndef COLOR_H_XWXGEHH1
#define COLOR_H_XWXGEHH1
#include <istream>

namespace yage {
namespace draw {

/**
 * A color in RGB, with alpha channel.
 */
class Color {
	private:
		double r_, g_, b_;
		double a_; ///< Alpha of the color; 0 for transparent and 1 for full color.

	public:
		Color(double r, double g, double b, double a = 1);
		Color(unsigned int ege_color);
		Color();

		double getr() const;
		double getg() const;
		double getb() const;
		double geta() const;

		void set_color(double r, double g, double b, double a = 1);
};

} // namespace draw
} // namespace yage
#endif /* end of include guard: COLOR_H_XWXGEHH1 */
