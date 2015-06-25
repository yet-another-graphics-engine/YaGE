#include "linear_gradient_color.h"

LinearGradientColor::LinearGradientColor(Color start_color, Color end_color,
                                         Point start_point, Point end_point)
{
  this->start_color = start_color;
  this->end_color = end_color;
  this->start_point = start_point;
  this->end_point = end_point;
}
