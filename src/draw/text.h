#ifndef TEXT_H_
#define TEXT_H_
#include "font.h"
#include "point.h"
#include "shape_property.h"

#include <string>

namespace yage {
namespace draw {

class Text : public ShapeProperty {
private:
    Font* font_;
    Point position_;

public:
    Text(std::string text, Font &font);

    std::string get_text(void) const;
    Font &get_font(void) const;
    Point &get_position(void);
    Color &get_color(void);

    void set_text(std::string text);
    void set_font(Font &font);
    // Set the left-top position of text
    void set_position(Point position);
    void set_color(Color &color);

};

}
}

#endif //TEXT_H_
