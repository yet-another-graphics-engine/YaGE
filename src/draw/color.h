#ifndef DRAW_COLOR_H_
#define DRAW_COLOR_H_

namespace yage {
namespace draw {

/**
 * A color in RGB, with alpha channel.
 */
struct Color {
	double r;
	double g;
	double b;
	double a; ///< Alpha of the color; 0 for transparent and 1 for full color.
	Color(double r = 0.0, double g = 0.0, double b = 0.0, double a = 1.0);
	Color(unsigned int ege_color);
};

} // namespace draw
} // namespace yage
#endif /* end of include guard: DRAW_COLOR_H_ */
