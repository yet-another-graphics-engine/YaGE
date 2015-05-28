#include "text.h"

using namespace yage::util;
namespace yage {
namespace draw {

Text::Text(const std::string &text) {
  set_text(text);
}

void Text::set_text(const std::string &text)
{
  text_ = convert_string(text);
}

std::string Text::get_text()
{
  return text_;
}

}
}
