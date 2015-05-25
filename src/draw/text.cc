#include "text.h"

namespace yage {
namespace draw {

Text::Text(std::string text, Font &font) : font_(&font), color(0.0, 0.0, 0.0, 1.0), text(text) {}

Font &Text::get_font(void) const {
    return *font_;
}

void Text::set_font(Font &font) {
    font_ = &font;
}

}
}
