#include "shape_property.h"
#include "color.h"

namespace yage {
namespace draw {

/**
 * Get the foreground(border) color of the shape.
 * @return the color
 */
Color ShapeProperty::get_fgcolor() const
{
    return fgcolor_;
}

/**
 * Get the background(fill) color of the shape.
 * @return the color
 */
Color ShapeProperty::get_bgcolor() const
{
    return bgcolor_;
}

/**
 * Get the border thickness of the shape.
 * @return the thickness
 */
double ShapeProperty::get_thickness() const
{
    return thickness_;
}

/**
 * Get the name of the shape.
 * @return the name
 */
std::string ShapeProperty::get_name() const
{
    return name_;
}

/**
 * Set the foreground(border) color of the shape.
 * @param fgcolor new foreground color
 */
void ShapeProperty::set_fgcolor(Color fgcolor)
{
    fgcolor_ = fgcolor;
}

/**
 * Set the background(fill) color of the shape.
 * @param fgcolor new background color
 */
void ShapeProperty::set_bgcolor(Color bgcolor)
{
    bgcolor_ = bgcolor;
}

/**
 * Set the border thickness of the shape.
 * @param fgcolor new thickness
 */
void ShapeProperty::set_thickness(double thickness)
{
    thickness_ = thickness;
}

/**
 * Rename the shape
 * @param name new name
 */
void ShapeProperty::set_name(std::string name)
{
    name_ = name;
}

/**
 * Initialize the shape to black bgcolor, black fgcolor, no border as the given
 * name.
 *
 * @param name the name of the shape
 */
ShapeProperty::ShapeProperty(std::string name, std::string type)
        : fgcolor_(), bgcolor_(), thickness_(1), name_(name), type_(type)
{
}

} // namespace draw
} // namespace yage
