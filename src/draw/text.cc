#include "text.h"

namespace yage {
namespace draw {

Text::Text(std::string text, Font &font) : text(text), color(1.0, 1.0, 1.0, 1.0), font_(&font) {}

Font &Text::get_font(void) const {
    return *font_;
}

void Text::set_font(Font &font) {
    font_ = &font;
}

}
}
