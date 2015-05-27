#include "font.h"
#include "../util/encoding.h"

namespace yage {
namespace draw {

Font::Font(std::string family, int size, bool is_bold, bool is_italic) {
  description_ = pango_font_description_new();
  set_font_family(family);
  set_size(size);
  set_bold_status(is_bold);
  set_italic_status(is_italic);
}

Font::Font(Font& font) {
  description_ = pango_font_description_copy(font.pro_get_pango_font());
}

Font &Font::operator=(Font &font) {
  if (this != &font) {
    pango_font_description_free(description_);
    description_ = pango_font_description_copy(font.pro_get_pango_font());
  }
  return *this;
}

Font::~Font() {
  pango_font_description_free(description_);
}

std::string Font::get_font_family(void) const {
  return pango_font_description_get_family(description_);
}

int Font::get_size(void) const {
  return pango_font_description_get_size(description_) / PANGO_SCALE;
}

bool Font::get_bold_status(void) const {
  return pango_font_description_get_weight(description_) > PANGO_WEIGHT_NORMAL;
}

bool Font::get_italic_status(void) const {
  return pango_font_description_get_style(description_) != PANGO_STYLE_NORMAL;
}

void Font::set_font_family(std::string family) {
  char *utf_8_family = yage::util::ansi_to_utf_8(family.c_str());
  pango_font_description_set_family(description_, utf_8_family);
  yage::util::free_string(utf_8_family);
}

void Font::set_size(int size) {
  pango_font_description_set_size(description_, size * PANGO_SCALE);
}

void Font::set_bold_status(bool is_bold) {
  if (is_bold) {
      pango_font_description_set_weight(description_, PANGO_WEIGHT_BOLD);
  } else {
      pango_font_description_set_weight(description_, PANGO_WEIGHT_NORMAL);
  }
}

void Font::set_italic_status(bool is_italic) {
  if (is_italic) {
      pango_font_description_set_style(description_, PANGO_STYLE_ITALIC);
  } else {
      pango_font_description_set_style(description_, PANGO_STYLE_NORMAL);
  }
}

PangoFontDescription *Font::pro_get_pango_font(void) const {
  return description_;
}

void Font::pro_set_pango_font(PangoFontDescription *description) {
  if (description_) this->~Font();
  description_ = description;
}

}
}
