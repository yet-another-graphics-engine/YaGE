#ifndef DRAW_TEXT_H_
#define DRAW_TEXT_H_
#include "font.h"
#include "point.h"
#include "color.h"

#include <string>

namespace yage {
namespace draw {

class Text {
private:
    Font* font_;

public:
    Point position;
    std::string text;

    Text(const std::string &text, Font &font);

    Font &get_font(void) const;

    void set_font(Font &font);
};

}
}

#endif //DRAW_TEXT_H_
