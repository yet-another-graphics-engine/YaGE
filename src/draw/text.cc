#include "text.h"

namespace yage {
namespace draw {

Text::Text(const std::string &text, Font &font) : font_(&font), text(text) {}

Font &Text::get_font(void) const {
    return *font_;
}

void Text::set_font(Font &font) {
    font_ = &font;
}

}
}
