#ifndef DRAW_TEXT_H_
#define DRAW_TEXT_H_
#include "font.h"
#include "point.h"
#include "color.h"

#include <string>

namespace yage {
namespace draw {

struct Text {
    Point position;
    std::string text;
    Text(const std::string &text = " ");
};

}
}

#endif //DRAW_TEXT_H_
