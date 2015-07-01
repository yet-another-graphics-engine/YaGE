#ifndef LINEARGRADIENTCOLOR_H
#define LINEARGRADIENTCOLOR_H
#include "color.h"
#include "point.h"

using namespace yage::draw;

namespace yage{
namespace draw{

struct LinearGradientColor
{
  Color start_color;
  Color end_color;
  Point start_point;
  Point end_point;

  LinearGradientColor(Color start_color, Color end_color, Point start_point, Point end_point);
};

}
}

#endif // LINEARGRADIENTCOLOR_H
