#ifndef DRAW_TEXT_H_
#define DRAW_TEXT_H_
#include "font.h"
#include "point.h"
#include "color.h"
#include "../util/encoding.h"
#include <string>

namespace yage {
namespace draw {

class Text {
  private:
    std::string text_;
  public:
    Point position;
    Text(const std::string &text = " ");
    void set_text(const std::string &text);
    std::string get_text();
};

}
}

#endif //DRAW_TEXT_H_
