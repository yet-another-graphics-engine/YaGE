#ifndef TEXT_H_
#define TEXT_H_
#include "font.h"
#include "point.h"
#include "shape_property.h"

#include <string>

namespace yage {
namespace draw {

class Text {
private:
    Font* font_;

public:
    Point position;
    Color color;
    std::string text;

    Text(std::string text, Font &font);

    Font &get_font(void) const;

    void set_font(Font &font);
};

}
}

#endif //TEXT_H_
