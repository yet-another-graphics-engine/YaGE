#ifndef BASIC_SHAPE_H_JZUADHOK
#define BASIC_SHAPE_H_JZUADHOK
#include "color.h"
#include "point.h"
#include <string>
#include <iostream>

namespace yage {
namespace draw {

/**
 * A base class for all shapes
 */
class BasicShape {
	protected:
		Color fgcolor_;		///< color of the border.
		Color bgcolor_;
		double thickness_;
		std::string name_;
		std::string type_;

	public:
		BasicShape(std::string name = "", std::string type = "");

		virtual ~BasicShape() = default;

		Color get_fgcolor() const;
		Color get_bgcolor() const;
		double get_thickness() const;
		std::string get_name() const;

		void set_fgcolor(Color fgcolor);
		void set_bgcolor(Color bgcolor);
		void set_thickness(double thickness);
		void set_name(std::string name);
};


} // namespace draw
} // namespace yage
#endif /* end of include guard: BASIC_SHAPE_H_JZUADHOK */
