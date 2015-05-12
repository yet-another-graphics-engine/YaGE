#include "text.h"

namespace yage {
namespace draw {

Text::Text(std::string text, Font &font) {
    bgcolor_ = Color(1.0, 1.0, 1.0, 1.0);
    name_ = text;
    font_ = &font;
}

std::string Text::get_text(void) const {
    return name_;
}

Font &Text::get_font(void) const {
    return *font_;
}

Point &Text::get_position(void) {
    return position_;
}

Color &Text::get_color(void) {
    return fgcolor_;
}

void Text::set_text(std::string text) {
    name_ = text;
}

void Text::set_font(Font &font) {
    font_ = &font;
}

void Text::set_position(Point &position) {
    position_ = position;
}

void Text::set_color(Color &color) {
    fgcolor_ = color;
}


}
}