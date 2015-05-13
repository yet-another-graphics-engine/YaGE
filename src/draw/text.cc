#include "text.h"
#ifdef _WIN32
#include "../platform/win32.h"
#include <cstdlib>
#endif

namespace yage {
namespace draw {

Text::Text(std::string text, Font &font) {
    bgcolor_ = Color(1.0, 1.0, 1.0, 1.0);
    set_text(text);
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
#ifndef _WIN32
    name_ = text;
#else
    char *ansi_str = yage::platform::ansi_to_utf_8(text.c_str());
    name_ = ansi_str;
    free(ansi_str);
#endif
}

void Text::set_font(Font &font) {
    font_ = &font;
}

void Text::set_position(Point position) {
    position_ = position;
}

void Text::set_color(Color &color) {
    fgcolor_ = color;
}


}
}
